/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:46:25 by noavetis          #+#    #+#             */
/*   Updated: 2025/10/29 02:05:01 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	push_token(t_token	**tokens, t_token *temp)
{
	t_token	*head;

	if (!*tokens)
		*tokens = temp;
	else
	{
		head = *tokens;
		while (head->next)
			head = head->next;
		head->next = temp;
		temp->prev = head;
	}
}

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		error_handle("Bad alloc!\n", 1);
	token->type = type;
	if (!value)
		error_handle("Bad alloc!\n", 1);
	token->value = value;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

bool	syntax_help(t_token *cur)
{
	if (is_redirect(cur->type) && cur->prev
		&& cur->prev->type == RPAR
		&& cur->next->next
		&& cur->next->next->type == WORD)
		return (check_type(cur->next->next), false);
	if (cur->prev && cur->prev->type == LPAR && cur->type == RPAR)
		return (check_type(cur), false);
	if (!cur->prev && (is_operator(cur->type) || cur->type == RPAR))
		return (check_type(cur), false);
	if (cur->type == HEREDOC)
	{
		if (cur->next && cur->next->next && cur->next->next->next
			&& (is_subshell(cur->next->next->type)
				|| is_redirect(cur->next->next->type)
				|| is_operator(cur->next->next->type))
			&& (is_subshell(cur->next->next->next->type)
				|| is_redirect(cur->next->next->next->type)
				|| is_operator(cur->next->next->next->type)))
		{
			cur->next->value = expand(cur->next->value, NULL, 1);
			fake_heredoc(cur->next->value, cur->l_count);
			return (check_type(cur->next->next), false);
		}
	}
	return (true);
}

bool	check_subs(t_token *input)
{
	int	c1;
	int	c2;

	c1 = 0;
	c2 = 0;
	while (input)
	{
		if (input->value && *input->value == '(')
			++c1;
		if (input->value && *input->value == ')')
			++c2;
		input = input->next;
	}
	if (c1 == c2)
		return (true);
	return (check_type(NULL), false);
}

void	init_sub_val(t_token **start, t_token **after, int *depth, bool *v)
{
	*start = NULL;
	*after = NULL;
	*depth = 0;
	*v = true;
}
