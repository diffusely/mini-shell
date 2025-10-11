/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:14:36 by noavetis          #+#    #+#             */
/*   Updated: 2025/10/11 21:27:53 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "shell.h"
# include "ast.h"

typedef struct s_shell		t_shell;
typedef struct s_ast		t_ast;
typedef struct s_redirect	t_redir;

// Exec
int		exec_pipe(t_shell *mish, t_ast *left, t_ast *right);
int		exec_cmd(t_shell *mish, t_ast *redir);
int		exec_ast_subtree(t_shell *mish, t_ast *subtree);
int		exec_sub(t_shell *mish);
int		heredoc(t_shell *mish, const char *delim, bool ex);
void	fake_heredoc(const char *delim);

// Utils
void	empty_cmd(t_shell *mish, t_ast *cmd);
void	dup_and_close(int fd[2], int new_fd, int close_read);
void	free_and_exit(t_shell *mish, int status);
void	exec_pip(t_shell *mish, t_ast *ast);
int		heredoc_helper(t_shell *mish, int status, int *fd, int ex);
#endif