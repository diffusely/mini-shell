/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:23:48 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/30 20:12:39 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

void	free_all(t_shell *mish)
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

void	free_split(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		free(str[i++]);
	free(str);
	str = NULL;
}

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	if (!tokens)
		return ;
	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->value);
		temp->value = NULL;
		free(temp);
		temp = NULL;
	}
}

void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->filename);
		redir->filename = NULL;
		free(redir);
		redir = NULL;
		redir = tmp;
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
