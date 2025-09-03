/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:02:07 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/03 16:08:54 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static t_ast	*parse_and(t_token **tokens);
static t_ast	*parse_pipe(t_token **tokens);
static t_ast	*parse_factor(t_token **tokens);
static t_ast	*parse_cmd(t_token **tokens);

t_ast	*create_tree(t_token **tokens)
{
	t_ast	*node;
	t_ast	*left;
	t_ast	*right;

	if (!tokens || !*tokens)
		return (NULL);
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

static t_ast	*parse_and(t_token **tokens)
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

static t_ast	*parse_pipe(t_token **tokens)
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

static t_ast	*parse_factor(t_token **tokens)
{
	t_ast	*sub;
	t_ast	*node;
	t_token	*r_tok;

	if (*tokens && (*tokens)->type == LPAR)
	{
		*tokens = (*tokens)->next;
		sub = create_tree(tokens);
		if (*tokens && (*tokens)->type == RPAR)
			*tokens = (*tokens)->next;
		node = create_node(NODE_SUB, NULL, sub);
		while (*tokens && is_redirect((*tokens)->type))
		{
			r_tok = *tokens;
			*tokens = (*tokens)->next;
			if (*tokens)
			{
				add_redir(node, r_tok->type, *tokens);
				*tokens = (*tokens)->next;
			}
		}
		return (node);
	}
	return (parse_cmd(tokens));
}

static void	helper(t_ast **node, t_token **tokens)
{
	t_token	*head;
	int	count;

	if (*tokens)
		*tokens = (*tokens)->next;
	count = 0;
	head = *tokens;
	while (head && head->type == WORD)
	{
		++count;
		head = head->next;
	}
	realoc_node(node, *tokens, count);
	while (*tokens && (*tokens)->type == WORD)
		*tokens = (*tokens)->next;
}

static t_ast	*parse_cmd(t_token **tokens)
{
	t_token	*r_tok;
	t_token	*head;
	t_ast	*node;
	int		count;

	head = *tokens;
	count = 0;
	node = ft_calloc(1, sizeof(t_ast));
	while (head && head->type == WORD)
	{
		++count;
		head = head->next;
	}
	init_node(&node, *tokens, count);
	while (*tokens && (*tokens)->type == WORD)
		*tokens = (*tokens)->next;
	while (*tokens && is_redirect((*tokens)->type))
	{
		r_tok = *tokens;
		*tokens = (*tokens)->next;
		add_redir(node, r_tok->type, *tokens);

		helper(&node, tokens);
	}
	return (node);
}
