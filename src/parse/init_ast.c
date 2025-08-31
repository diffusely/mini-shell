/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:30:27 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/31 19:45:44 by noavetis         ###   ########.fr       */
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

void	add_redir(t_ast *node, t_token_type type, t_token *t)
{
	t_redir	*redir;

	if (!t)
		return ;
	redir = ft_calloc(1, sizeof(t_redir));
	if (type == IN)
		redir->type = R_IN;
	else if (type == OUT)
		redir->type = R_OUT;
	else if (type == HEREDOC)
		redir->type = R_HEREDOC;
	else
		redir->type = R_APPEND;
	redir->filename = ft_strdup(t->value);
	redir->next = node->redirs;
	node->redirs = redir;
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
	(*node)->redirs = NULL;
}
