/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:48:25 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/15 21:28:16 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static int	help_cmd(t_shell *mish)
{
	int	status;

	status = 0;
	if (is_built(mish->tree->cmd))
	{
		if (mish->tree->redirs)
			create_files(mish, mish->tree->redirs);
		exec_built(mish->tree->cmd, &mish->list_env, mish);
		dup2(mish->fd_in, STDIN_FILENO);
		dup2(mish->fd_out, STDOUT_FILENO);
	}
	else
		status = exec_cmd(mish, mish->tree);
	return (status);
}

static int	help_and_or(t_shell *mish, int flag)
{
	int	status;

	status = exec_ast_subtree(mish, mish->tree->left);
	if (flag && status == 0)
		status = exec_ast_subtree(mish, mish->tree->right);
	else if (status != 0)
		status = exec_ast_subtree(mish, mish->tree->right);
	return (status);
}

int	exec_ast(t_shell *mish)
{
	if (!mish->tree)
		return (0);
	if (mish->tree->type == NODE_CMD)
		return (help_cmd(mish));
	else if (mish->tree->type == NODE_PIP)
		return (exec_pipe(mish, mish->tree->left, mish->tree->right));
	else if (mish->tree->type == NODE_AND)
		return (help_and_or(mish, 1));
	else if (mish->tree->type == NODE_OR)
		return (help_and_or(mish, 0));
	else if (mish->tree->type == NODE_SUB)
		return (exec_sub(mish));
	return (0);
}
