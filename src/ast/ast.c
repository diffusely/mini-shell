/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:48:53 by noavetis          #+#    #+#             */
/*   Updated: 2025/06/20 19:38:37 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// t_ast	*create_node(t_node_type type)
// {
// 	t_ast_tree	*res;

// 	res = ft_calloc(1, sizeof(t_ast_tree));
// 	if (!res)
// 		error_handle("Bad alloc!\n", 1);
// 	res->node = type;
// 	res->value = NULL;
// 	res->next = NULL;

// 	return (res);
// }

// void	free_tree(t_ast *root)
// {
// }

void print_ast(t_ast *node, int depth)
{
	if (!node)
		return;

	for (int i = 0; i < depth; ++i)
		printf("  ");

	if (node->type == NODE_PIP)
		printf("PIPE\n");
	else if (node->type == NODE_CMD)
	{
		printf("COMMAND:");
		for (int i = 0; node->argv[i]; ++i)
			printf(" %s", node->argv[i]);
		printf("\n");
	}

	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}
