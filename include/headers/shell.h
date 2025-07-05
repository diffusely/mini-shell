/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:09:57 by noavetis          #+#    #+#             */
/*   Updated: 2025/07/05 17:50:01 by vmakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include "get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>

void	sigint_handler(int signum);
char	*ft_strncpy(char *dest, const char *src, size_t n);
int		open_fd(int fd);
void 	history_settings(int fd, char *input, char *history, int history_size);

#endif