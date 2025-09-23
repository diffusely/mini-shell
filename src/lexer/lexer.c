/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:06:06 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/23 22:48:08 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*word_dup(int *i, const char *line)
{
	int	start;

	start = *i;
	while (line[*i] && !is_and(line, *i) && !ft_strchr("|><()", line[*i])
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
		if (line[*i])
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

bool	syntax_check(t_token *input)
{
	t_token	*cur;

	cur = input;
	while (cur)
	{
		if (cur->type == LPAR)
			break ;
		if (cur->type == RPAR)
			return (check_type(cur), false);
		cur = cur->next;
	}
	return (syntax_validation(input) && check_subs(input));
}

void	check_type(t_token *tok)
{
	ft_err("minishell: syntax error near unexpected token `");
	if (tok)
		ft_err(tok->value);
	else
		ft_err("newline");
	ft_err("'\n");
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
