/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:59:16 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/28 22:57:00 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool	is_redirect(t_token_type type)
{
	return (type == IN || type == OUT || type == APPEND || type == HEREDOC);
}

bool	is_operator(t_token_type type)
{
	return (type == OR || type == AND || type == PIP);
}

int	is_space_or_newline(char *input)
{
	while (*input)
	{
		if (!ft_isspace(*input))
			return (false);
		input++;
	}
	return (true);
}

void	check_type(t_token_type type)
{
	ft_err("minishell: syntax error near unexpected token `");
	if (type == PIP)
		ft_err("|");
	else if (type == OR)
		ft_err("||");
	else if (type == AND)
		ft_err("&&");
	else if (type == OUT)
		ft_err(">");
	else if (type == APPEND)
		ft_err(">>");
	else if (type == IN)
		ft_err("<");
	else if (type == HEREDOC)
		ft_err("<<");
	else if (type == LPAR)
		ft_err("(");
	else if (type == RPAR)
		ft_err(")");
	else
		ft_err("newline");
	ft_err("'\n");
}
