/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:16:28 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/14 21:45:45 by noavetis         ###   ########.fr       */
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
		status2 = 128 + WTERMSIG(status2); 
	return (status2);
}

static void	start(t_shell *mish, int *fd, int *pid1)
{
	if (pipe(fd) == -1)
		free_exit_msg(mish, "minishell: pip error\n");
	*pid1 = fork();
	if (*pid1 == -1)
		free_exit_msg(mish, "minishell: fork error\n");
}

static void	help_pid1(t_shell *mish, t_ast *left, int *status)
{
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
			if (left && left->redirs && left->redirs->type != R_HEREDOC)
				create_files(mish, left->redirs);
			empty_cmd(mish, left);
			exec_pip(mish, left);
		}
	}
	else
		exec_built(left->cmd, &mish->list_env, mish);
}

static void	help_pid2(t_shell *mish, t_ast *right, int *status)
{
	if (!is_built(right->cmd))
	{
		if (right->type == NODE_SUB)
		{
			*status = exec_ast_subtree(mish, right->left);
			free_and_exit(mish, *status);
		}
		else
		{
			if (right && right->redirs && right->redirs->type != R_HEREDOC)
				create_files(mish, right->redirs);
			empty_cmd(mish, right);
			exec_pip(mish, right);
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
	signal(SIGINT, sig_handler);
    signal(SIGQUIT, sig_handler);
	start(mish, fd, &pid1);
	if (pid1 == 0)
	{
		dup_and_close(fd, STDOUT_FILENO, 0);
		help_pid1(mish, left, &status);
		free_and_exit(mish, status);
	}
	pid2 = fork();
	if (pid2 == -1)
		free_exit_msg(mish, "minishell: fork error\n");
	if (pid2 == 0)
	{
		dup_and_close(fd, STDIN_FILENO, 1);
		help_pid2(mish, right, &status);
		free_and_exit(mish, status);
	}
	return (check_pipe_status(fd, pid1, pid2));
}
