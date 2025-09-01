/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:22:02 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/01 20:04:03 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "libft.h"
# include "lexer.h"
# include "shell.h"
# include "ast.h"

typedef struct s_ast		t_ast;
typedef struct s_token		t_token;
typedef struct s_shell		t_shell;
typedef struct s_redirect	t_redir;

// Free
void	free_mish(t_shell *mish);
void	free_all(t_shell *mish);
void	free_tree(t_ast *root);

// Utils
void	free_tokens(t_token *tokens);
void	free_redirs(t_redir *redir);
void	free_split(char **str);

#endif