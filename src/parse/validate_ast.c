/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 01:35:20 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/15 03:25:49 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static bool	is_empty_cmd(t_ast *n)
{
	return (n->type == NODE_CMD && (!n->cmd
			|| !n->cmd[0] || n->cmd[0][0] == '\0'));
}

static void	and_or_error(t_node_type type)
{
	ft_err("minishell: syntax error near unexpected token `");
	if (type == NODE_OR)
		ft_err("||");
	else
		ft_err("&&");
	ft_err("'\n");
}

static bool	conditions(t_ast *node)
{
	if (node->type == NODE_PIP && (!node->right || !node->left
			|| is_empty_cmd(node->right)
			|| is_empty_cmd(node->left)))
	{
		ft_err("minishell: syntax error near unexpected token `|'\n");
		return (false);
	}
	else if (node->type == NODE_SUB && (!node->right
			|| node->right->type != NODE_CMD || is_empty_cmd(node->right)))
	{
		ft_err("minishell: syntax error near unexpected token `newline'\n");
		return (false);
	}
	else if ((node->type == NODE_OR || node->type == NODE_AND)
		&& (!node->right || !node->left
			|| is_empty_cmd(node->right) || is_empty_cmd(node->left)))
	{
		and_or_error(node->type);
		return (false);
	}
	return (true);
}

bool	validate_ast(t_ast *node)
{
	if (!node)
		return (false);
	if (!conditions(node))
		return (false);
	if (node->left && !validate_ast(node->left))
		return (false);
	if (node->right && !validate_ast(node->right))
		return (false);
	return (true);
}
