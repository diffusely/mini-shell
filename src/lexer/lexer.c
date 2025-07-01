/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:06:06 by noavetis          #+#    #+#             */
/*   Updated: 2025/07/01 19:51:56 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token_type	token_type(char first, char second)
{
	if (first == '\0')
		return (END);
	if (first == '<' && second == '<')
		return (HEREDOC);
	if (first == '>' && second == '>')
		return (APPEND);
	if (first == '&' && second == '&')
		return (AND);
	if (first == '|' && second == '|')
		return (OR);
	if (first == '>')
		return (OUT);
	if (first == '<')
		return (IN);
	if (first == '|')
		return (PIP);
	if (first == '(')
		return (LPAR);
	if (first == ')')
		return (RPAR);
	return (WORD);
}

static char	*token_value(t_token_type type)
{
	char*	res;

	res = NULL;
    if (type == END)
        res = ft_strdup("");
    else if (type == HEREDOC)
        res = ft_strdup("<<");
    else if (type == APPEND)
        res = ft_strdup(">>");
    else if (type == AND)
        res = ft_strdup("&&");
    else if (type == OR)
        res = ft_strdup("||");
    else if (type == OUT)
        res = ft_strdup(">");
    else if (type == IN)
        res = ft_strdup("<");
    else if (type == PIP)
        res = ft_strdup("|");
    else if (type == LPAR)
        res = ft_strdup("(");
    else if (type == RPAR)
        res = ft_strdup(")");
    return (res);
}

static char	*word_dup(int *i, const char *line)
{
	int	start;

	start = *i;
	while (line[*i] && token_type(line[*i], line[*i + 1]) == WORD)
		++(*i);
	return (ft_substr(line, start, *i - start));
}

t_token	*lexer(const char *line)
{
	t_token			*tokens;
	t_token			*temp;
	t_token_type	type;
	char			*res;
	int				i;

	if (!line)
		return (NULL);
	i = 0;
	tokens = NULL;
	while (line[i])
	{
		type = token_type(line[i], line[i + 1]);
		if (type == WORD)
			res = word_dup(&i, line);
		else if (type == HEREDOC || type == APPEND || type == AND || type == OR)
		{
			res = token_value(type);
			i += 2;
		}
		else
		{
			res = token_value(type);
			++i;
		}
		temp = create_token(type, res);
		push_token(&tokens, temp);		
	}
	return (tokens);
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

t_token *create_token(t_token_type type, char *value)
{
	t_token *token;

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

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	if (!tokens)
		return ;
	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->value);
		temp->value = NULL;
		free(temp);
		temp = NULL;
	}
}

void	print_tokens(t_token *lexer)
{
	while (lexer)
	{
		ft_printf("%d -> %s\n", lexer->type, lexer->value);
		lexer = lexer->next;
	}
}
