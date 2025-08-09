/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:09:57 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/07 18:31:51 by vmakarya         ###   ########.fr       */
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


typedef struct s_ast t_ast;
typedef struct s_token t_token;

void	sigint_handler(int signum);


//	history
void	print_history(t_ast *tree, char *input, t_token *token);
bool	is_history(char *input);
void	add_history_input(t_ast *tree, char *input, t_token *token);
int		open_fd(t_ast *tree, char *input, t_token *token);

// commands
int		exec_pwd(const char *path);
bool	exec_cd(const char *input, t_list *envp_list);
void	exec_env(char *input, t_list **list_env);
void	check_unset(char *input, t_list **env_list);
void	init_env(char **envp, t_list **list_env);
void	exec_home(const char *input);

#endif