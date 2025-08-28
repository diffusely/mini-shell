/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:37:58 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/29 01:48:02 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static bool	check_errors(t_token *cur)
{
	if (is_operator(cur->type)
		&& (!cur->next || is_operator(cur->next->type)))
	{
		if (cur->next)
			check_type(cur->next->type);
		else
			check_type(cur->type);
		return (false);
	}
	if ((is_redirect(cur->type)) && (!cur->next || cur->next->type != WORD))
	{
		if (cur->next)
			check_type(cur->next->type);
		else
			check_type(END);
		return (false);
	}
	return (true);
}

static bool	check_end(t_token *input)
{
	t_token	*last;

	last = input;
	while (last->next)
		last = last->next;
	if (is_redirect(last->type) || is_operator(last->type))
		return (check_type(last->type), false);
	return (true);
}

static t_token	*condition(t_token **st, t_token **after, t_token *tmp, bool *v)
{
	bool	res;

	*after = tmp->next;
	if (tmp->prev)
		tmp->prev->next = NULL;
	if (*st)
		res = syntax_validation(*st);
	else
		res = true;
	if (tmp->prev)
		tmp->prev->next = tmp;
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
			if (*depth < 0)
				return (*valid = false, check_type(RPAR), NULL);
			if (*depth == 0)
				return (condition(&start, &after, tmp, valid));
		}
		tmp = tmp->next;
	}
	if (*depth > 0)
		return (check_type(LPAR), *valid = false, NULL);
	return (NULL);
}

bool	syntax_validation(t_token *input)
{
	t_token	*cur;
	bool	valid;
	int		depth;

	if (!input)
		return (true);
	if (is_operator(input->type) || input->type == RPAR)
		return (check_type(input->type), false);
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
		else if (cur->type == RPAR)
			return (check_type(RPAR), false);
		if (!check_errors(cur))
			return (false);
		cur = cur->next;
	}
	return (check_end(input));
}
