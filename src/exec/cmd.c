/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:19:22 by noavetis          #+#    #+#             */
/*   Updated: 2025/10/29 01:03:02 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	print_error(const char *cmd, char *path, int flag)
{
	if (ft_strchr(cmd, '/') && errno == 2)
		ft_err(": No such file or directory\n");
	else if (path && !ft_strcmp(path, "Error"))
		ft_err(": command not found\n");
	else if (errno == EACCES && flag == -1)
		ft_err(": Permission denied\n");
	else if (errno == EACCES && flag == 0)
		ft_err(": Is a directory\n");
	else if (errno == ENOEXEC)
		ft_err(": Exec format error\n");
	else
	{
		ft_err(": ");
		ft_err(strerror(errno));
		ft_err("\n");
	}
}

int	print_exec_error(const char *cmd, char *path)
{
	int	flag;

	if (!cmd)
		return (1);
	ft_err("minishell: ");
	ft_err((char *)cmd);
	flag = access(cmd, X_OK);
	print_error(cmd, path, flag);
	if (path && (!ft_strcmp(path, "Error") || errno == 2))
		return (127);
	else if (errno == EACCES)
		return (126);
	return (errno);
}

void	exec_commands(t_shell *mish)
{
	char	*path;
	char	*cmd;
	int		exit_code;

	cmd = mish->tree->cmd[0];
	path = get_path(mish, cmd);
	if (path)
		execve(path, mish->tree->cmd, mish->env);
	exit_code = print_exec_error(cmd, path);
	if (path)
		free(path);
	free_and_exit(mish, exit_code);
}

static void	helper(int *status)
{
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else
	{
		*status = 128 + WTERMSIG(*status);
		if (*status == 130)
			printf("\n");
		if (*status == 131)
			printf("Quit (core dumped)\n");
	}
	set_signals_prompt();
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
			status = create_files(mish, redir->redirs, true);
		set_signals_exec();
		if (status == 0)
		{
			empty_cmd(mish, mish->tree);
			exec_commands(mish);
		}
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	return (helper(&status), status);
}
