/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:37:58 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/23 22:50:04 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static bool	check_errors(t_token *cur)
{
	if (is_operator(cur->type) && (!cur->next || is_operator(cur->next->type)
			|| cur->next->type == RPAR))
	{
		if (cur->next)
			return (check_type(cur->next), false);
		return (check_type(cur), false);
	}
	if (cur->type == WORD && cur->prev && cur->prev->type == RPAR)
		return (check_type(cur), false);
	if (cur->type == WORD && cur->next && cur->next->type == LPAR)
	{
		if (!cur->next->next)
			return (check_type(cur->next), false);
		return (check_type(cur->next->next), false);
	}
	if ((is_redirect(cur->type)) && (!cur->next || cur->next->type != WORD))
	{
		if (cur->next)
			return (check_type(cur->next), false);
		return (check_type(NULL), false);
	}
	if (!syntax_help(cur))
		return (false);
	return (true);
}

static bool	check_end(t_token *input)
{
	t_token	*last;

	last = input;
	while (last->next)
		last = last->next;
	if (is_redirect(last->type) || is_operator(last->type))
		return (check_type(last), false);
	return (true);
}

static t_token	*condition(t_token **st, t_token **after, t_token *tmp, bool *v)
{
	bool	res;

	*after = tmp->next;
	tmp->next = NULL;
	if (*st)
		res = syntax_validation(*st);
	else
		res = true;
	tmp->next = *after;
	if (!res)
		return (*v = false, NULL);
	return (*after);
}

static t_token	*check_subshell(t_token *tmp, bool *valid, int *depth)
{
	t_token	*start;
	t_token	*after;

	init_sub_val(&start, &after, depth, valid);
	while (tmp)
	{
		if (tmp->type == LPAR)
		{
			if (*depth == 0)
				start = tmp->next;
			++(*depth);
		}
		else if (tmp->type == RPAR)
		{
			--(*depth);
			if (tmp->next && tmp->next->type == LPAR)
				return (check_type(tmp), *valid = false, NULL);
			if (*depth == 0)
				return (condition(&start, &after, tmp, valid));
		}
		tmp = tmp->next;
	}
	if (*depth > 0)
		return (check_type(NULL), *valid = false, NULL);
	return (NULL);
}

bool	syntax_validation(t_token *input)
{
	t_token	*cur;
	bool	valid;
	int		depth;

	if (!input)
		return (true);
	cur = input;
	while (cur)
	{
		if (cur->type == LPAR)
		{
			cur = check_subshell(cur, &valid, &depth);
			if (!valid)
				return (false);
			continue ;
		}
		if (!check_errors(cur))
			return (false);
		if (cur->type == WORD && check_quoted(cur->value))
			return (check_type(NULL), false);
		cur = cur->next;
	}
	return (check_end(input));
}
