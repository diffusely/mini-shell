/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:37:59 by vmakarya          #+#    #+#             */
/*   Updated: 2025/09/22 21:18:20 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

int	exec_pwd(t_shell *mish, const char *input)
{
	char	*pwd;

	(void)input;
	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		printf("%s\n", pwd);
		return (free(pwd), 0);
	}
	pwd = find_list("PWD", &mish->list_env);
	if (pwd)
	{
		printf("%s\n", pwd);
		return (0);
	}
	ft_err("minishell: pwd error\n");
	return (1);
}
