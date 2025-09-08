/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:19:22 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/09 00:59:27 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	fd_error(t_shell *mish, t_redir *r)
{
	ft_err("minishell: ");
	if (r->filename)
		perror(r->filename);
	free_all(mish);
	exit(1);
}

void	create_files(t_shell *mish, t_redir *r)
{
	int	fd;

	while (r)
	{
		if (r->type == R_OUT)
			fd = open(r->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (r->type == R_APPEND)
			fd = open(r->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (r->type == R_IN)
			fd = open(r->filename, O_RDONLY);
		if (fd < 0)
			fd_error(mish, r);
		if (r->type == R_OUT || r->type == R_APPEND)
			dup2(fd, STDOUT_FILENO);
		else
			dup2(fd, STDIN_FILENO);
		close(fd);
		r = r->next;
	}
}

static void	exec_commands(t_shell *mish)
{
	char	*path;

	path = NULL;
	path = get_path(mish, mish->tree->cmd[0]);
	execve(path, mish->tree->cmd, mish->env);
	if (mish->tree->cmd[0] && mish->tree->cmd[0][0])
		ft_err(mish->tree->cmd[0]);
	ft_err(": command not found\n");
	if (path)
		free(path);
	free_and_exit(mish, 127);
}

int	exec_cmd(t_shell *mish, t_ast *redir)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		error_handle("minishell: fork error\n", 0);
	status = 0;
	if (pid == 0)
	{
		if (redir->redirs)
			create_files(mish, redir->redirs);
		if (!mish->tree->cmd[0] || mish->tree->cmd[0][0] == '\0')
		{
			free_all(mish);
			exit(0);
		}
		exec_commands(mish);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else
		status = 1;
	return (status);
}
