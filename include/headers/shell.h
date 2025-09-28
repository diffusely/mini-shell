/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:26:24 by vmakarya          #+#    #+#             */
/*   Updated: 2025/09/28 13:35:07 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include "message.h"
# include "get_next_line.h"
# include "free.h"
# include "built.h"


# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <dirent.h>

typedef struct s_ast			t_ast;
typedef struct s_token			t_token;
typedef enum e_token_type		t_token_type;

extern volatile sig_atomic_t	g_signal;

typedef struct s_shell
{
	char			**env;
	t_token			*token;
	t_token			*free_token;
	t_ast			*tree;
	char			*input;
	int				status;
	int				fd_in;
	int				fd_out;
	t_list			*list_env;
	struct s_shell	*free;
}	t_shell;

// Signals
void	sigint_handler(int signum);
void	set_signals_prompt(void);
void	set_signals_exec(void);
void	set_signals_heredoc(void);
void	sigint_handler_heredoc(int sig);
void	sig_handler(int sig);

// Shell
t_shell	*init_shell(char **envp);
void	shell_loop(t_shell *mish);
char	*get_path(t_shell *mish, char *cmd);
char	**wildcard_expand(const char *pattern);
void	create_wildcard_tok(t_token *tmp,t_token *cur ,char **match);

#endif