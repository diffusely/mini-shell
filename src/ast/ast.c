/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:48:53 by noavetis          #+#    #+#             */
/*   Updated: 2025/07/22 23:42:04 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void print_ast(t_ast *node, int depth)
{
	if (!node)
		return;

	for (int i = 0; i < depth; ++i)
		printf("  ");

	if (node->type == NODE_PIP)
		printf("PIPE\n");
	if (node->type == NODE_AND)
		printf("AND\n");
	if (node->type == NODE_OR)
		printf("OR\n");
	if (node->type == NODE_SUB)
		printf("SUBSHELL\n");
	else if (node->type == NODE_CMD)
	{
		printf("COMMAND:");
		for (int i = 0; node->cmd[i]; ++i)
			printf(" %s", node->cmd[i]);
		printf("\n");
	}

	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}

void	execute_ast()
{

}
