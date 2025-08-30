/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:59:16 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/30 21:55:37 by noavetis         ###   ########.fr       */
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
