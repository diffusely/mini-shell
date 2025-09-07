/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 21:27:32 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/08 01:34:26 by noavetis         ###   ########.fr       */
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
typedef struct s_shell	t_shell;

typedef enum e_built
{
	NONE,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	HISTORY,
	EXIT
}	t_built;

// Exec
bool	exec_cd(char *input, t_list **envp_list);
bool	exec_echo(char *input, t_list **list_env);
int		exec_env(char *input, t_list **list_env);
int		exec_history(char **cmd);
int		exec_pwd(const char *input);
void	exec_exit(char **cmd, t_shell *mish);

// Functions
char	*fix_new_line(bool new_line, char *input);
void	check_dollar(char *input, t_list **list_env);
void	print_env(t_list *env);

// Utils
int		find_word_place(char *word);
int		exec_built(char **cmd, t_list **envp_list, t_shell *mish);
int		is_built(char **cmd);

#endif