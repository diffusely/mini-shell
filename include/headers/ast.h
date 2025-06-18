/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:03:48 by noavetis          #+#    #+#             */
/*   Updated: 2025/06/18 18:49:58 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "lexer.h"

typedef enum e_node
{
	NODE_CMD,
	NODE_PIP,
	NODE_RDIR
}	t_node_type;

typedef enum e_redir_type
{
	RDIR_IN,      // <
	RDIR_OUT,     // >
	RDIR_HEREDOC, // <<
	RDIR_APPEND   // >>
}	t_redir_type;

typedef struct s_redirect
{
	t_redir_type		type;
	char				*filename;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_ast_tree
{
	t_node_type			node;
	char				**argv;      // for exceve
	t_redirect			*redir_list;
	struct s_ast_tree	*left;
	struct s_ast_tree	*right;
}	t_ast_tree;


t_ast_tree	*create_node(t_node_type type);
t_ast_tree	*parse_tokens(t_token **tokens);
void		free_tree(t_ast_tree *root);
void		print_tree(t_ast_tree *root, int level);

#endif
