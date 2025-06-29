/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:02:07 by noavetis          #+#    #+#             */
/*   Updated: 2025/06/29 19:11:59 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	split_tokens(t_token *tokens, t_token **left, t_token **right)
{
	t_token	*current;

	current = tokens;
	*left = tokens;
	*right = NULL;
	while (current)
	{
		if (current->type == PIP)
		{
			*right = current->next;
			current->next = NULL;
			return ;
		}
		current = current->next;
	}
}

t_ast	*parse_pipe(t_token *tokens)
{
	t_token	*left_tokens;
	t_token	*right_tokens;
	t_ast	*left_node;
	t_ast	*right_node;
	t_ast	*new_node;

	if (!tokens)
		return (NULL);
	split_tokens(tokens, &left_tokens, &right_tokens);
	left_node = parse_cmd(left_tokens);
	while (right_tokens)
	{
		split_tokens(right_tokens, &left_tokens, &right_tokens);
		right_node = parse_cmd(left_tokens);
		new_node = ft_calloc(1, sizeof(t_ast));
		new_node->type = NODE_PIP;
		new_node->ptr = NULL;
		new_node->left = left_node;
		new_node->right = right_node;
		left_node = new_node;
	}
	return (left_node);
}

static void	init_node(t_ast **node, t_token *tokens)
{
	int	i;

	i = 0;
	(*node)->ptr = tokens;
	while (tokens && tokens->type != PIP)
	{
		(*node)->argv[i++] = ft_strdup(tokens->value);
		tokens = tokens->next;
	}
	(*node)->argv[i] = NULL;
	(*node)->type = NODE_CMD;
	(*node)->left = NULL;
	(*node)->right = NULL;
}

t_ast	*parse_cmd(t_token *tokens)
{
	t_token	*head;
	t_ast	*node;
	int		count;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		error_handle("Bad alloc!\n", 1);
	count = 0;
	head = tokens;
	node->ptr = tokens;
	while (head && head->type != PIP)
	{
		++count;
		head = head->next;
	}
	node->argv = ft_calloc(count + 1, sizeof(char *));
	if (!node->argv)
		error_handle("Bad alloc!\n", 1);
	init_node(&node, tokens);
	return (node);
}
