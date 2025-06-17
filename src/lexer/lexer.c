/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:06:06 by noavetis          #+#    #+#             */
/*   Updated: 2025/06/17 23:14:08 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token_type	token_type(const char *token)
{
	if (!token)
		return END;
	if (token[0] == '<' && token[1] == '<')
		return HEREDOC;
	if (token[0] == '>' && token[1] == '>')
		return APPEND;
	if (token[0] == '>')
		return OUT;
	if (token[0] == '<')
		return IN;
	if (token[0] == '|')
		return PIP;
	return WORD;
}

static t_token	*init_token(t_token_type type, const char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		exit(1);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
		exit(1);
	token->next = NULL;
	return (token);
}

t_token	*lexer(const char *line)
{
	t_token	*tokens;
	t_token	*temp;
	char	**res;
	int		i;

	i = 0;
	tokens = NULL;
	res = ft_split(line, ' ');
	while (res && res[i])
	{
		temp = init_token(token_type(res[i]), res[i]);
		push_token(&tokens, temp);
		++i;
	}
	return (free_split(res), tokens);
}

void push_token(t_token	**tokens, t_token *temp)
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

void free_tokens(t_token *tokens)
{
	t_token	*temp;

	if (!tokens)
		return ;
	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->value);
		free(temp);
		temp = NULL;
	}
}

void print_tokens(t_token *lexer)
{
	while (lexer)
	{
		ft_printf("%d -> %s\n", lexer->type, lexer->value);
		lexer = lexer->next;
	}
}
