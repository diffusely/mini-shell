/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 21:27:32 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/21 21:31:56 by noavetis         ###   ########.fr       */
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
int		exec_cd(t_shell **shell, char **input, t_list **envp_list, int i);
bool	exec_echo(char **cmd, t_list **list_env);
int		exec_env(char *input, t_list **list_env);
int		exec_history(char **cmd);
int		exec_pwd(const char *input);
void	exec_exit(char **cmd, t_shell *mish);
bool	exec_unset(char **cmd, t_list **envp);
bool	exec_export(char **cmd, t_list **envp_list);

// Functions
void	print_env(t_list *env);
char	*remove_quotes(char *str);

// Utils
void	ft_err_msg(char *str, char *msg);
int		f_w_p(char *word);
int		exec_built(char **cmd, t_list **envp_list, t_shell *mish);
int		is_built(char **cmd);

#endif