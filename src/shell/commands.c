/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:54:54 by noavetis          #+#    #+#             */
/*   Updated: 2025/07/22 21:08:45 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	exec_cd(const char *input)
{
	while (*input && ft_isspace(*input))
		input++;
	if (!ft_strncmp(input, "cd", 2))
		input += 2;
	else
		return (false);
	while (*input && ft_isspace(*input))
		input++;
	if (!(*input))
	{
		if (chdir(getenv("HOME")) == 0)
			return (true);
	}
	if (chdir(input) == 0)
		return (true);
	printf("cd: no such file or directory: %s\n", input);
	return (false);
}

int	exec_pwd(const char *input)
{
	char	*pwd;

	if (!input)
		return (false);
	while (*input && ft_isspace(*input))
		input++;
	if (!ft_strncmp(input, "pwd", 3))
		input += 2;
	else
		return (true);
	while (*input && ft_isspace(*input))
		input++;
	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
		return (true);
	}
	return (false);
}
