/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:02:07 by noavetis          #+#    #+#             */
/*   Updated: 2025/07/04 21:09:41 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_ast *create_node(t_node_type type, t_ast *right, t_ast *left)
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

t_ast *parse_expr(t_token **tokens)
{
	t_ast	*node;
	t_ast	*left;
	t_ast	*right;

	left = parse_and(tokens);
	while (*tokens && (*tokens)->type == OR)
	{
		*tokens = (*tokens)->next;
		right = parse_and(tokens);
		node = create_node(NODE_OR, right, left);
		left = node;
	}
	return (left);
}

t_ast *parse_and(t_token **tokens)
{
	t_ast	*node;
	t_ast	*left;
	t_ast	*right;

	left = parse_pipe(tokens);
	while (*tokens && (*tokens)->type == AND)
	{
		*tokens = (*tokens)->next;
		right = parse_pipe(tokens);
		node = create_node(NODE_AND, right, left);
		left = node;
	}
	return (left);
}

t_ast *parse_pipe(t_token **tokens)
{
	t_ast	*node;
	t_ast	*left;
	t_ast	*right;

	left = parse_factor(tokens);
	while (*tokens && (*tokens)->type == PIP)
	{
		*tokens = (*tokens)->next;
		right = parse_factor(tokens);
		node = create_node(NODE_PIP, right, left);
		left = node;
	}
	return (left);
}

t_ast *parse_factor(t_token **tokens)
{
	t_ast	*sub;
	t_ast	*node;

	if (*tokens && (*tokens)->type == LPAR)
	{
		*tokens = (*tokens)->next;
		sub = parse_expr(tokens);
		if (!*tokens || (*tokens)->type != RPAR)
			error_handle("Missing )\n", 1);
		*tokens = (*tokens)->next;
		node = create_node(NODE_SUB, NULL, sub);
		return (node);
	}
	return parse_cmd(tokens);
}

static void	init_node(t_ast **node, t_token *tokens, int count)
{
	int	i;

	(*node)->cmd = malloc(sizeof(char *) * (count + 1));
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

t_ast	*parse_cmd(t_token **tokens)
{
	t_token	*head;
	t_ast	*node;

	if (!*tokens || (*tokens)->type != WORD)
		error_handle("Syntax error: expected command\n", 1);
	head = *tokens;
	node = ft_calloc(1, sizeof(t_ast));
	int count = 0;
	while (head && head->type == WORD)
	{
		++count;
		head = head->next;
	}
	init_node(&node, *tokens, count);
	while (*tokens && (*tokens)->type == WORD)
		*tokens = (*tokens)->next;
	return (node);
}
