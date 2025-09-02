/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:48:25 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/02 19:56:20 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int exec_ast(t_shell *mish)
{
	char *path;
	int status = 0;

	if (!mish->tree)
		return 0;
	path = NULL;
	if (mish->tree->type == NODE_CMD)
	{
		if (is_built(mish->tree->cmd))
		{
			if (mish->tree->redirs)
				return (exec_redir(mish, mish->tree));
			exec_built(mish->tree->cmd, &mish->list_env);
		}
		else
		{
			if (mish->tree->redirs)
				return exec_redir(mish, mish->tree);
			{
				if (mish->tree->cmd[0] && mish->tree->cmd[0][0])
					path = get_path(mish, mish->tree->cmd[0]);
				status = exec_cmd(mish, path, mish->tree->cmd, mish->env);
				if (path)
					free(path);
			}
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
