/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 22:33:58 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/22 23:03:32 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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

bool	is_and(const char *line, int i)
{
	if (line[i] && line[i + 1] && line[i] == '&' && line[i + 1] == '&')
		return (true);
	return (false);
}

bool	valid_cmd(char *input)
{
	if (!input)
		return (true);
	return (false);
}
