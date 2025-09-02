/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 21:27:32 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/02 19:41:52 by noavetis         ###   ########.fr       */
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

typedef enum e_built
{
	NONE,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_built;

// Exec
bool	exec_cd(char *input, t_list **envp_list);
bool	exec_echo(char *input, t_list **list_env);
bool	exec_env(char *input, t_list **list_env);
bool	exec_pwd(const char *input);

// Functions
char	*fix_new_line(bool new_line, char *input);
void	check_dollar(char *input, t_list **list_env);
void	print_env(t_list *env);

// Utils
int		find_word_place(char *word);
int		exec_built(char **cmd, t_list **envp_list);
int		is_built(char **cmd);

#endif