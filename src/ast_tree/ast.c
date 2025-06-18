/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:48:53 by noavetis          #+#    #+#             */
/*   Updated: 2025/06/18 19:01:29 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_ast_tree *create_node(t_node_type type)
{
	t_ast_tree	*res;

	res = ft_calloc(1, sizeof(t_ast_tree));
	if (!res)
		error_handle("Bad alloc!\n", 1);
	res->node = type;

	return (res);
}

t_ast_tree *parse_tokens(t_token **tokens)
{
	t_token	*head;

	head = *tokens;
	while (head)
	{
		head = head->next;
	}
}

void free_tree(t_ast_tree *root)
{

	
}

void print_tree(t_ast_tree *root, int level)
{


}
