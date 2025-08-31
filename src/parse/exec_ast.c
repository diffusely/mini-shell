/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:48:25 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/31 18:25:46 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static int	exec_ast_subtree(t_shell *mish, t_ast *subtree)
{
	t_shell temp;

	temp = *mish;
	temp.tree = subtree;
	return (exec_ast(&temp));
}

static int	exec_cmd(char *cmd, char **args, char **envp)
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
			if (args[0])
				ft_err(args[0]);
			ft_err(": command not found\n");
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

static int	exec_sub(t_shell *mish)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		error_handle("minishell: fork error\n", 0);
	if (pid == 0)
	{
		status = exec_ast_subtree(mish, mish->tree->right);
		exit(status);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else
		status = 1;
	return (status);
}

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

static int	exec_pipe(t_shell *mish, t_ast *left, t_ast *right)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	*path_left;
	char	*path_right;

	if (pipe(fd) == -1)
		error_handle("minishell: fork error\n", 0);
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
		
		if (!check_builtins(left->cmd, &mish->list_env))
		{
			path_left = get_path(mish, left->cmd[0]);
			execve(path_left, left->cmd, mish->env);
			free(path_left);
			if (left->cmd[0])
				ft_err(left->cmd[0]);
			error_handle(": command not found\n", 1);
		}
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

		
		if (!check_builtins(right->cmd, &mish->list_env))
		{
			path_right = get_path(mish, right->cmd[0]);
			execve(path_right, right->cmd, mish->env);
			free(path_right);
			if (right->cmd[0])
				ft_err(right->cmd[0]);
			error_handle(": command not found\n", 1);
		}
		exit(0);
	}
	return (check_pipe_status(fd, pid1, pid2));
}

int exec_ast(t_shell *mish)
{
	char *path;
	int status = 0;

	if (!mish->tree)
		return 0;

	if (mish->tree->type == NODE_CMD)
	{
		if (!check_builtins(mish->tree->cmd, &mish->list_env))
		{
			path = get_path(mish, mish->tree->cmd[0]);
			status = exec_cmd(path, mish->tree->cmd, mish->env);
			free(path);
		}
		return status;
	}
	else if (mish->tree->type == NODE_PIP)
	{
		status = exec_pipe(mish, mish->tree->left, mish->tree->right);
		return status;
	}
	else if (mish->tree->type == NODE_AND)
	{
		status = exec_ast_subtree(mish, mish->tree->left);
		if (status == 0)
			status = exec_ast_subtree(mish, mish->tree->right);
		return status;
	}
	else if (mish->tree->type == NODE_OR)
	{
		status = exec_ast_subtree(mish, mish->tree->left);
		if (status != 0)
			status = exec_ast_subtree(mish, mish->tree->right);
		return status;
	}
	else if (mish->tree->type == NODE_SUB)
	{
		status = exec_sub(mish);
		return (status);
	}
	return (status);
}
