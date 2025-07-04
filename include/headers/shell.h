/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:09:57 by noavetis          #+#    #+#             */
/*   Updated: 2025/07/04 21:44:31 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include "get_next_line.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

void	sigint_handler(int signum);
int		ft_isspace(char c);
#endif