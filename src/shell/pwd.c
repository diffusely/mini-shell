/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:54:46 by vmakarya          #+#    #+#             */
/*   Updated: 2025/07/22 15:55:14 by vmakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	exec_pwd(const char *input)
{
	char	*pwd;

	if (!input)
		return (false);
	while (*input && ft_isspace(*input))
		input++;
	if (!ft_strncmp(input, "pwd", 7))
		input += 2;
	else
		return (1);
	while (*input && ft_isspace(*input))
		input++;
	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
		return (1);
	}
	return (0);
}
