/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:37:59 by vmakarya          #+#    #+#             */
/*   Updated: 2025/08/31 01:04:29 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

bool	exec_pwd(const char *input)
{
	char	*pwd;

	if (!input)
		return (false);
	input += 3;
	while (*input && is_quoted(*input))
		input++;
	if (*input)
		return (false);
	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
		return (true);
	}
	ft_err("minishell: pwd error");
	return (true);
}
