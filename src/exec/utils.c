/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:06:18 by noavetis          #+#    #+#             */
/*   Updated: 2025/10/29 00:57:00 by noavetis         ###   ########.fr       */
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
	if (!cmd->cmd[0])
	{
		free_all(mish);
		exit(0);
	}
	if (cmd->cmd[0][0] == '\0')
	{
		ft_err("minishell: command not found\n");
		free_all(mish);
		exit(127);
	}
}

void	exec_pip(t_shell *mish, t_ast *ast)
{
	char	*path;
	char	*cmd;
	int		exit_code;

	cmd = ast->cmd[0];
	path = get_path(mish, cmd);
	if (path)
		execve(path, ast->cmd, mish->env);
	exit_code = print_exec_error(cmd, path);
	if (path)
		free(path);
	free_and_exit(mish, exit_code);
}

int	heredoc_helper(t_shell *mish, int status, int *fd, int ex)
{
	if ((WIFEXITED(status) && WEXITSTATUS(status) == 130)
		|| WIFSIGNALED(status))
	{
		close(fd[0]);
		if (ex)
			free_and_exit(mish, 130);
		return (1);
	}
	return (0);
}
