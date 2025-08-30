/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:06:06 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/30 15:36:59 by noavetis         ###   ########.fr       */
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
	char	*res;

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
	while (!is_and(line, *i) && !ft_strchr("|><()", line[*i])
		&& line[*i] != ' ')
	{
		if (line[*i] == '"')
		{
			++(*i);
			while (line[*i] && line[*i] != '"')
				++(*i);
		}
		else if (line[*i] == '\'')
		{
			++(*i);
			while (line[*i] && line[*i] != '\'')
				++(*i);
		}
		++(*i);
	}
	return (ft_substr(line, start, *i - start));
}

static bool	help_lex(const char *line, char *res, t_token **t, int *i)
{
	t_token_type	type;

	while (line[*i] && ft_isspace(line[*i]))
		++(*i);
	if (!line[*i])
		return (false);
	type = token_type(line[*i], line[*i + 1]);
	if (type == WORD)
		res = word_dup(i, line);
	else
	{
		res = token_value(type);
		if (type == HEREDOC || type == APPEND
			|| type == AND || type == OR)
			*i += 2;
		else
			++(*i);
	}
	push_token(t, create_token(type, res));
	return (true);
}

t_token	*lexer(const char *line)
{
	t_token			*tokens;
	char			*res;
	int				i;

	i = 0;
	tokens = NULL;
	res = NULL;
	while (line && line[i])
	{
		if (!help_lex(line, res, &tokens, &i))
			break ;
	}
	return (tokens);
}
