/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:34:24 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/13 19:50:15 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_H
# define MESSAGE_H

# include "libft.h"
# include "shell.h"
# include "ast.h"

typedef struct s_ast	t_ast;
typedef struct s_shell	t_shell;

void	error_print(const char *cmd, const char *msg, int flag);
void	error_handle(char *msg, int flag);
void	error_exit_msg(t_shell *mish, t_ast *left, char *msg);
void	ft_err(char *msg);
void	free_exit_msg(t_shell *mish, char *msg);

#endif