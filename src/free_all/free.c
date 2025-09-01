/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:23:48 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/01 20:08:48 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

void	free_mish(t_shell *mish)
{
	if (mish->tree)
	{
		free_tree(mish->tree);
		mish->tree = NULL;
	}
	if (mish->input)
	{
		free(mish->input);
		mish->input = NULL;
	}
	if (mish->free_token)
	{
		free_tokens(mish->free_token);
		mish->free_token = NULL;
	}
}

void	free_all(t_shell *mish)
{
	if (mish)
	{
		free_mish(mish);
		free(mish->env);
		ft_lstclear(&mish->list_env);
		free(mish);
	}
}

void	free_tree(t_ast *root)
{
	int	i;

	if (!root)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	i = 0;
	if (root->type == NODE_CMD || root->type == NODE_SUB)
	{
		while (root->cmd && root->cmd[i])
			free(root->cmd[i++]);
		free(root->cmd);
		root->cmd = NULL;
		if (root->redirs)
			free_redirs(root->redirs);
	}
	free(root);
}
