/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:09:57 by noavetis          #+#    #+#             */
/*   Updated: 2025/07/22 21:26:04 by noavetis         ###   ########.fr       */
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

void	sigint_handler(int signum);


//	history
void	print_history(t_ast *tree, char *input, t_token *token);
bool	is_history(char *input);
void	add_history_input(t_ast *tree, char *input, t_token *token);
int		open_fd(t_ast *tree, char *input, t_token *token);

// commands
int		exec_pwd(const char *path);
int		exec_cd(const char *path);

#endif