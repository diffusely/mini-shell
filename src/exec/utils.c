/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:06:18 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/21 23:59:40 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_and_exit(t_shell *mish, int status)
{
	free_all(mish);
	exit(status);
}

void	dup_and_close(int fd[2], int new_fd, int close_read)
{
	if (close_read)
	{
		close(fd[1]);
		dup2(fd[0], new_fd);
		close(fd[0]);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], new_fd);
		close(fd[1]);
	}
}

void	empty_cmd(t_shell *mish, t_ast *cmd)
{
	if (!cmd->cmd[0] || cmd->cmd[0][0] == '\0')
	{
		free_all(mish);
		exit(2);
	}
}

void	exec_pip(t_shell *mish, t_ast *ast)
{
	char	*path;

	path = NULL;
	path = get_path(mish, ast->cmd[0]);
	if (path)
		execve(path, ast->cmd, mish->env);
	if (path)
		free(path);
	error_exit_msg(mish, ast, ": command not found\n");
}
