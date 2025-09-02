/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:46:25 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/02 22:36:40 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	print_tokens(t_token *lexer)
{
	while (lexer)
	{
		printf("%d -> %s\n", lexer->type, lexer->value);
		lexer = lexer->next;
	}
}

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
	return (true);
}
