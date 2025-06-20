/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:03:48 by noavetis          #+#    #+#             */
/*   Updated: 2025/06/20 21:50:33 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "lexer.h"
# include "free.h"
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

typedef struct s_ast
{
	t_node_type			type;
	char				**argv;      // for exceve
	t_redirect			*redir_list;
	struct s_ast		*left;
	struct s_ast		*right;
}	t_ast;

t_ast		*create_node(t_node_type type);
t_ast		*parse_pipe(t_token *tokens);
t_ast		*parse_cmd(t_token *tokens);
void		free_tree(t_ast *root);
void		print_ast(t_ast *node, int depth);

#endif
