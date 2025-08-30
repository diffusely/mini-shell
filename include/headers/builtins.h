/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 21:27:32 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/30 23:23:37 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"
# include "shell.h"
# include "message.h"
# include "get_next_line.h"
# include "free.h"

typedef struct s_list	t_list;

// Exec
bool	exec_cd(const char *input, t_list **envp_list);
bool	exec_echo(char *input, t_list **list_env);
bool	exec_env(char *input, t_list **list_env);
bool	exec_pwd(const char *input);

// Functions
char	*fix_new_line(bool new_line, char *input);
void	check_dollar(char *input, t_list **list_env);
void	print_env(t_list *env);

// Utils
int		find_word_place(char *word);
bool	check_builtins(char **cmd, t_list **envp_list);

#endif