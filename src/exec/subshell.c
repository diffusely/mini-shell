/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:14:23 by noavetis          #+#    #+#             */
/*   Updated: 2025/10/19 00:00:40 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_ast_subtree(t_shell *mish, t_ast *subtree)
{
	t_shell	temp;

	temp = *mish;
	temp.tree = subtree;
	return (exec_ast(&temp));
}

static void	help_end(pid_t pid, int *status)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else
		*status = 128 + WTERMSIG(*status);
	set_signals_prompt();
}

static bool	helper(t_shell *mish, int *status)
{
	t_ast	*tree;

	if (mish->tree->redirs)
	{
		tree = mish->tree;
		mish->tree = mish->tree->left;
		*status = create_files(mish, tree->redirs, true);
		if (*status == 0)
			*status = exec_ast_subtree(mish, mish->tree);
		return (false);
	}
	return (true);
}

int	exec_sub(t_shell *mish)
{
	pid_t	pid;
	int		status;
	t_ast	*mish_free;

	mish_free = mish->tree;
	pid = fork();
	if (pid == -1)
		error_handle("minishell: fork error\n", 0);
	if (pid == 0)
	{
		set_signals_exec();
		if (helper(mish, &status))
			status = exec_ast_subtree(mish, mish->tree->left);
		mish->tree = mish_free;
		free_and_exit(mish, status);
	}
	return (help_end(pid, &status), status);
}
