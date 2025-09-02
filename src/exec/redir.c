/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:17:23 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/02 19:55:48 by noavetis         ###   ########.fr       */
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

static void	create_files(t_shell *mish, t_redir *r)
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
		else if (r->type == R_HEREDOC)
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

static void	exec_commands(t_shell *mish, int *status)
{
	char	*path;

	path = NULL;
	if (is_built(mish->tree->cmd))
	{
		*status = exec_built(mish->tree->cmd, &mish->list_env);
		return ;
	}
	if (mish->tree->cmd[0] && mish->tree->cmd[0][0])
		path = get_path(mish, mish->tree->cmd[0]);
	if (mish->tree->cmd[0] && mish->tree->cmd[0][0] != '\0')
		*status = exec_cmd(mish, path, mish->tree->cmd, mish->env);
	if (path)
		free(path);
}

int	exec_redir(t_shell *mish, t_ast *redir)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		error_handle("minishell: fork error\n", 0);
	if (pid == 0)
	{
		create_files(mish, redir->redirs);
		exec_commands(mish, &status);
		exit(status);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
