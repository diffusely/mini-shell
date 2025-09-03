/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:14:23 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/03 19:35:18 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_ast_subtree(t_shell *mish, t_ast *subtree)
{
	t_shell temp;

	temp = *mish;
	temp.tree = subtree;
	return (exec_ast(&temp));
}

int	exec_sub(t_shell *mish)
{
	pid_t	pid;
	int		status;
	t_shell	*mish_free = mish;
	t_ast	*tree;

	pid = fork();
	if (pid == -1)
		error_handle("minishell: fork error\n", 0);
	if (pid == 0)
	{
		if (mish->tree->redirs)
		{
			tree = mish->tree;
			mish->tree = mish->tree->left;
			status = exec_cmd(mish, tree);
		}
		else
			status = exec_ast_subtree(mish, mish->tree->left);
		free_all(mish_free);
		exit(status);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else
		status = 1;
	return (status);
}
