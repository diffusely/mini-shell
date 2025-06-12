/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:42:04 by noavetis          #+#    #+#             */
/*   Updated: 2025/05/14 16:18:29 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"

# include "fcntl.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>

typedef struct s_pip
{
	int		fout;
	int		fin;
	char	**path;
	char	***cmd;
	int		**fd;
	pid_t	*pid;
	int		size;
	char	**envp;
}	t_pip;

char	*get_path(t_pip *pip, char *cmd);
void	error_print(const char *cmd, const char *msg, int flag);
void	error_handle(char *msg, int flag);
void	free_all(t_pip *pip);
void	free_split(char **str);
void	pipex(t_pip *pip);
void	init_pipex_val(t_pip *pip, char **argv, char **envp, int argc);
void	here_doc(t_pip *pip, char **argv, int argc);
void	init_cmd_and_pid(t_pip *pip, char **argv, int add);
void	init_here_doc_val(t_pip *pip, char **argv, char **envp, int argc);
void	init_path(t_pip *pip);
void	init_fd(t_pip *pip);

#endif