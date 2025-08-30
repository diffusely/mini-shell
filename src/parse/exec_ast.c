/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:48:25 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/30 20:39:28 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static void exec_cmd(char *cmd, char *args[], char *envp[])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_handle("fork error\n", 0);
	if (pid == 0)
	{
		if (execve(cmd, args, envp) == -1)
			error_handle(args[0], 0);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		error_handle("fork error\n", 0);
}

void	exec_ast(t_shell *mish, char **env)
{
	char	*path;
	if (!mish->tree)
		return ;

	if (mish->tree->type == NODE_CMD)
	{
		path = get_path(mish, mish->tree->cmd[0]);
		exec_cmd(path, mish->tree->cmd, env);
		free(path);
	}
}
