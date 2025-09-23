/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 22:55:42 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/22 23:11:13 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_token_type	token_type(char first, char second)
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

int	is_built(char **cmd)
{
	char	*tmp;

	if (!cmd || !cmd[0] || !cmd[0][0])
		return (NONE);
	tmp = *cmd;
	if (ft_strncmp(tmp, "echo", 4) == 0)
		return (ECHO);
	if (ft_strncmp(tmp, "cd", 2) == 0)
		return (CD);
	else if (ft_strcmp(tmp, "pwd") == 0)
		return (PWD);
	else if (ft_strncmp(tmp, "export", 6) == 0)
		return (EXPORT);
	else if (ft_strncmp(tmp, "unset", 5) == 0)
		return (UNSET);
	else if (ft_strcmp(tmp, "env") == 0)
		return (ENV);
	else if (ft_strcmp(tmp, "exit") == 0)
		return (EXIT);
	else if (ft_strcmp(tmp, "history") == 0)
		return (HISTORY);
	return (NONE);
}

char	*token_value(t_token_type type)
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
