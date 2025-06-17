/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:03:48 by noavetis          #+#    #+#             */
/*   Updated: 2025/06/17 18:27:10 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef enum e_node
{
	NODE_CMD,
	NODE_PIP,
	NODE_RDIR
}	t_node_type;

typedef enum e_redir_type
{
	RDIR_IN,
	RDIR_OUT,
	RDIR_HEREDOC,
	RDIR_APPEND
}	t_redir_type;

typedef struct s_ast_tree
{
	t_redir_type		redir;
	t_node_type			node;
	struct s_ast_tree	*child;
	struct s_ast_tree	*left;
	struct s_ast_tree	*right;
}	t_ast_tree;

#endif
