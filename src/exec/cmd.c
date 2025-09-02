/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:19:22 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/02 15:19:39 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_cmd(t_shell *mish, char *cmd, char **args, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		error_handle("minishell: fork error\n", 0);
	if (pid == 0)
	{
		if (execve(cmd, args, envp) == -1)
		{
			if (args[0] && args[0][0])
				ft_err(args[0]);
			ft_err(": command not found\n");
			free(cmd);
			free_all(mish);
			exit(127);
		}
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else
		status = 1;
	return (status);
}
