/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:16:28 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/07 22:00:47 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	check_pipe_status(int *fd, pid_t pid1, pid_t pid2)
{
	int	status1;
	int	status2;

	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
		status2 = WEXITSTATUS(status2);
	else
		status2 = 1;
	return (status2);
}

static void	start(t_shell *mish, int *fd, int *pid1)
{
	if (pipe(fd) == -1)
	{
		free_all(mish);
		error_handle("minishell: pip error\n", 0);
	}
	*pid1 = fork();
	if (*pid1 == -1)
	{
		free_all(mish);
		error_handle("minishell: fork error\n", 0);
	}
}

static void	help_pid1(t_shell *mish, t_ast *left, int *status)
{
	char	*path;

	if (left->type == NODE_PIP)
	{
		*status = exec_pipe(mish, left->left, left->right);
		free_and_exit(mish, *status);
	}
	if (!is_built(left->cmd))
	{
		if (left->type == NODE_SUB)
		{
			*status = exec_ast_subtree(mish, left->left);
			free_and_exit(mish, *status);
		}
		else
		{
			if (left && left->redirs)
				create_files(mish, left->redirs);
			if (!left->cmd[0] || left->cmd[0][0] == '\0')
			{
				free_all(mish);
				exit(0);
			}
			path = get_path(mish, left->cmd[0]);
			execve(path, left->cmd, mish->env);
			if (path)
				free(path);
			error_exit_msg(mish, left, ": command not found\n");
		}
	}
	else
		exec_built(left->cmd, &mish->list_env, mish);
}

static void	help_pid2(t_shell *mish, t_ast *right, int *status)
{
	char	*path;

	if (!is_built(right->cmd))
	{
		if (right->type == NODE_SUB)
		{
			*status = exec_ast_subtree(mish, right->left);
			free_and_exit(mish, *status);
		}
		else
		{
			if (right && right->redirs)
				create_files(mish, right->redirs);
			if (!right->cmd[0] || right->cmd[0][0] == '\0')
			{
				free_all(mish);
				exit(0);
			}
			path = get_path(mish, right->cmd[0]);
			execve(path, right->cmd, mish->env);
			if (path)
				free(path);
			error_exit_msg(mish, right, ": command not found\n");
		}
	}
	else
		exec_built(right->cmd, &mish->list_env, mish);
}

int	exec_pipe(t_shell *mish, t_ast *left, t_ast *right)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	status = 0;
	start(mish, fd, &pid1);
	if (pid1 == 0)
	{
		dup_and_close(fd, STDOUT_FILENO, 0);
		help_pid1(mish, left, &status);
		free_and_exit(mish, status);
	}
	pid2 = fork();
	if (pid2 == -1)
		error_handle("minishell: fork error\n", 0);
	if (pid2 == 0)
	{
		dup_and_close(fd, STDIN_FILENO, 1);
		help_pid2(mish, right, &status);
		free_and_exit(mish, status);
	}
	return (check_pipe_status(fd, pid1, pid2));
}
