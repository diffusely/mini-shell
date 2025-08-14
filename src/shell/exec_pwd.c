/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:37:59 by vmakarya          #+#    #+#             */
/*   Updated: 2025/08/14 16:09:55 by vmakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

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
