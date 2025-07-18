/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:23:48 by noavetis          #+#    #+#             */
/*   Updated: 2025/07/18 20:19:00 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

void	free_all(t_ast *tree, char *input, t_token *token)
{
	if (tree)
	{
		free_tree(tree);
		tree = NULL;
	}
	if (input)
	{
		free(input);
		input = NULL;
	}
	if (token)
	{
		free_tokens(token);
		token = NULL;
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

void	free_tree(t_ast *root)
{
	if (!root)
		return ;

	//printf("free_ast: type %d\n", root->type);
	free_tree(root->left);
	free_tree(root->right);

	int i = 0;
	while (root->type == NODE_CMD && root->cmd && root->cmd[i])
	{
		free(root->cmd[i++]);
	}
	if (root->type == NODE_CMD)
	{
		free(root->cmd);
		root->cmd = NULL;
	}
	free(root);
}
