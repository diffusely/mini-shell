/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:46:25 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/14 22:09:38 by noavetis         ###   ########.fr       */
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
	return (token);
}
