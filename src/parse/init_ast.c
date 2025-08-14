/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:30:27 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/14 21:15:21 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_ast	*create_node(t_node_type type, t_ast *right, t_ast *left)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		error_handle("Bad alloc!\n", 1);
	node->type = type;
	node->cmd = NULL;
	node->left = left;
	node->right = right;
	return (node);
}

void	init_node(t_ast **node, t_token *tokens, int count)
{
	int	i;

	(*node)->cmd = ft_calloc((count + 1), sizeof(char *));
	if (!(*node)->cmd)
		error_handle("Bad alloc for cmd\n", 1);
	i = 0;
	while (tokens && i < count)
	{
		(*node)->cmd[i++] = ft_strdup(tokens->value);
		tokens = tokens->next;
	}
	(*node)->cmd[i] = NULL;
	(*node)->type = NODE_CMD;
	(*node)->left = NULL;
	(*node)->right = NULL;
}
