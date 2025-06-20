/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:02:07 by noavetis          #+#    #+#             */
/*   Updated: 2025/06/20 20:33:30 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void split_tokens(t_token *tokens, t_token **left, t_token **right)
{
	t_token *current = tokens;
	*left = tokens;
	*right = NULL;

	while (current)
	{
		if (current->type == PIP)
		{
			*right = current->next;
			current->next = NULL;
			return;
		}
		current = current->next;
	}
}

t_ast	*parse_pipe(t_token *tokens)
{
	t_token	*left;
	t_token	*right;
	t_ast	*node;

	if (!tokens)
		return NULL;

	split_tokens(tokens, &left, &right);

	if (right)
	{
		node = ft_calloc(1, sizeof(t_ast));
		node->type = NODE_PIP;
		node->left = parse_pipe(left);
		node->right = parse_pipe(right);
		return (node);
	}
	return (parse_cmd(left));
}

t_ast	*parse_cmd(t_token *tokens)
{
	t_token	*head;
	t_ast	*node;
	int		i;
	int		count;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		error_handle("Bad alloc!\n", 1);
	count = 0;
	head = tokens;
	while (head && head->type != PIP)
	{
		++count;
		head = head->next;
	}
	node->argv = ft_calloc(count + 1, sizeof(char *));
	i = 0;
	while (tokens)
	{
		node->argv[i++] = ft_strdup(tokens->value);
		tokens = tokens->next;
	}
	node->argv[count] = NULL;
	node->type = NODE_CMD;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
