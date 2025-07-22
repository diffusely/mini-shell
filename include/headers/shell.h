/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:09:57 by noavetis          #+#    #+#             */
/*   Updated: 2025/07/22 15:56:09 by vmakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include "message.h"
# include "get_next_line.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
#include <unistd.h>

void	sigint_handler(int signum);
int		open_fd();

//	history
void	print_history();
bool	is_history(char *input);
void	add_history(const char *input);
int		exec_pwd(const char *path);
int		exec_cd(const char *path);

#endif