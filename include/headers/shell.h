/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:26:24 by vmakarya          #+#    #+#             */
/*   Updated: 2025/08/29 16:55:48 by noavetis         ###   ########.fr       */
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

typedef struct s_ast		t_ast;
typedef struct s_token		t_token;
typedef enum e_token_type	t_token_type;

typedef struct	s_shell
{
	t_token	*token;
	t_token	*free_token;
	char	*input;
	t_ast	*tree;
	t_list	*list_env;
}	t_shell;

void	sigint_handler(int signum);

// History
void	print_history(t_shell *mish);
bool	is_history(char *input);
void	add_history_input(t_shell *mish);
int		open_fd(t_shell *mish);

// Functions
int		is_space_or_newline(char *input);
void	print_env(t_list *env);
// Commands
int		exec_pwd(const char *path);
bool	exec_cd(const char *input, t_list **envp_list);
bool	exec_env(char *input, t_list **list_env);
bool	check_unset(char *input, t_list **env_list);
t_list	*init_env(char **envp);
int		find_word_place(char *word);

// void	exec_home(const char *input);
bool	check_builtins(char *cmd, t_list **list_env);
bool	remove_list(const char *input, t_list **envp_list);

// Utils
bool	is_redirect(t_token_type type);
bool	is_operator(t_token_type type);
bool	is_subshell(t_token_type type);
void	check_type(t_token *tok);

#endif