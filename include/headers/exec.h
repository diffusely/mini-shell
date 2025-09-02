/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:14:36 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/02 18:41:31 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "shell.h"
# include "ast.h"

typedef struct s_shell	t_shell;
typedef struct s_ast	t_ast;

// Exec
int	exec_cmd(t_shell *mish, char *cmd, char **args, char **envp);
int	exec_pipe(t_shell *mish, t_ast *left, t_ast *right);
int	exec_redir(t_shell *mish, t_ast *redir);
int	exec_ast_subtree(t_shell *mish, t_ast *subtree);
int	exec_sub(t_shell *mish);
int	exex_built_redir(t_shell *mish, t_ast *redir);

#endif