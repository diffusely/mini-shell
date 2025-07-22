/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:03:48 by noavetis          #+#    #+#             */
/*   Updated: 2025/07/22 21:41:44 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "lexer.h"

//typedef struct s_token t_token;

typedef enum e_node
{
	NODE_CMD,
	NODE_PIP,
	NODE_AND,
	NODE_OR,
	NODE_SUB,   // ()

	
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

typedef struct s_ast
{
	t_node_type			type;
	t_redirect			*redir_list;

	char				**cmd;      // for exceve
	struct s_ast		*left;
	struct s_ast		*right;
}	t_ast;

t_ast	*create_node(t_node_type type, t_ast *right, t_ast *left);

// Parse
t_ast	*parse_expr(t_token **tokens);
t_ast	*parse_and(t_token **tokens);
t_ast	*parse_pipe(t_token **tokens);
t_ast	*parse_factor(t_token **tokens);
t_ast	*parse_cmd(t_token **tokens);




void	print_ast(t_ast *node, int depth);

#endif
