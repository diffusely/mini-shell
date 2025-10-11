/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:19:22 by noavetis          #+#    #+#             */
/*   Updated: 2025/10/11 21:28:40 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	exec_commands(t_shell *mish)
{
	char	*path;

	path = NULL;
	path = get_path(mish, mish->tree->cmd[0]);
	if (path)
		execve(path, mish->tree->cmd, mish->env);
	if (mish->tree->cmd[0] && mish->tree->cmd[0][0])
		ft_err(mish->tree->cmd[0]);
	ft_err(": command not found\n");
	if (path)
		free(path);
	free_and_exit(mish, 127);
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
	int		pid;
	int		status;

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
