/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:16:28 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/03 19:38:32 by noavetis         ###   ########.fr       */
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

int	exec_pipe(t_shell *mish, t_ast *left, t_ast *right)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	*path_left;
	char	*path_right;

	if (pipe(fd) == -1)
		error_handle("minishell: pip error\n", 0);
	pid1 = fork();
	if (pid1 == -1)
		error_handle("minishell: fork error\n", 0);
	if (pid1 == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);

		if (left->type == NODE_PIP)
			exit(exec_pipe(mish, left->left, left->right));
		
			
		if (!is_built(left->cmd))
		{
			if (left->type == NODE_SUB)
				exit(exec_ast_subtree(mish, left->left));
			else
			{
				path_left = get_path(mish, left->cmd[0]);
				execve(path_left, left->cmd, mish->env);
				free(path_left);
				if (left->cmd[0] && left->cmd[0][0])
					ft_err(left->cmd[0]);
				free_all(mish);
				error_handle(": command not found\n", 1);
			}
		}
		else
			exec_built(left->cmd, &mish->list_env);
		//free_all(mish);
		exit(0);
	}

	pid2 = fork();
	if (pid2 == -1)
		error_handle("minishell: fork error\n", 0);

	if (pid2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);

		
		if (!is_built(right->cmd))
		{
			if (right->type == NODE_SUB)
				exit(exec_ast_subtree(mish, right->left));
			else
			{
				path_right = get_path(mish, right->cmd[0]);
				execve(path_right, right->cmd, mish->env);
				free(path_right);
				if (right->cmd[0] && right->cmd[0][0])
					ft_err(right->cmd[0]);
				free_all(mish);
				error_handle(": command not found\n", 1);
			}
		}
		else
			exec_built(right->cmd, &mish->list_env);
		//free_all(mish);
		exit(0);
	}
	return (check_pipe_status(fd, pid1, pid2));
}

