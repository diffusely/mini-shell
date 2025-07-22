/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:09:57 by noavetis          #+#    #+#             */
/*   Updated: 2025/07/22 23:58:01 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include "message.h"
# include "get_next_line.h"
# include "free.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_ast	t_ast;
typedef struct s_token	t_token;

void	sigint_handler(int signum);

// History
void	print_history(t_ast *tree, char *input, t_token *token);
bool	is_history(char *input);
void	add_history_input(t_ast *tree, char *input, t_token *token);
int		open_fd(t_ast *tree, char *input, t_token *token);

// Commands
bool	exec_pwd(const char *path);
bool	exec_cd(const char *path);

// Functions
int		is_space_or_newline(char *input);

#endif