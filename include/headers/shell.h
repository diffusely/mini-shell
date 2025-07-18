/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:09:57 by noavetis          #+#    #+#             */
/*   Updated: 2025/07/18 17:04:07 by noavetis         ###   ########.fr       */
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

void	sigint_handler(int signum);
int		open_fd();

//	history
void	print_history();
bool	is_history(char *input);
void	add_history(const char *input);

#endif