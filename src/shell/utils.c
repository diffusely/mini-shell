/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:59:16 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/29 16:53:39 by noavetis         ###   ########.fr       */
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

bool	is_subshell(t_token_type type)
{
	return (type == RPAR || type == LPAR);
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

void	check_type(t_token *tok)
{
	ft_err("minishell: syntax error near unexpected token `");
	if (tok)
		ft_err(tok->value);
	else
		ft_err("newline");
	ft_err("'\n");
}
