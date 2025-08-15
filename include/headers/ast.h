/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:27:11 by vmakarya          #+#    #+#             */
/*   Updated: 2025/08/15 03:25:35 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "lexer.h"

typedef struct s_token	t_token;

typedef enum e_node
{
	NODE_CMD,
	NODE_PIP,
	NODE_AND,
	NODE_OR,
	NODE_SUB,
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

typedef struct s_ast
{
	t_node_type			type;
	t_redirect			*redir_list;

	char				**cmd;      // for exceve
	struct s_ast		*left;
	struct s_ast		*right;
}	t_ast;

// Creat node
t_ast	*create_node(t_node_type type, t_ast *right, t_ast *left);
void	init_node(t_ast **node, t_token *tokens, int count);

// Parse
t_ast	*create_tree(t_token **tokens);

// Print ast
void	print_ast(t_ast *node, int depth);

// Validation
bool	validate_ast(t_ast *node);

#endif