/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 01:43:04 by noavetis          #+#    #+#             */
/*   Updated: 2025/10/12 19:08:36 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	ctrl_d_message(const char *delim, char *line)
{
	ft_err("minishell: ");
	ft_err("warning: ");
	ft_err("here-document at line 1 delimited by end-of-file ");
	ft_err("(wanted `");
	ft_err((char *)delim);
	ft_err("')\n");
	free(line);
}

void	fake_heredoc(const char *delim)
{
	pid_t	pid;
	char	*line;

	pid = fork();
	if (pid == -1)
		error_handle("*FORK* error!\n", 1);
	if (pid == 0)
	{
		give_heredoc_signals();
		while (1)
		{
			line = readline("> ");
			if (!line || ft_strcmp(line, delim) == 0)
			{
				ctrl_d_message(delim, line);
				break ;
			}
			free(line);
		}
		exit(0);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	wait(NULL);
}

void	help_heredic(char *line, const char *delim, int *fd)
{
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delim) == 0)
		{
			ctrl_d_message(delim, line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
}

static void	helper(int *fd, pid_t pid, int *status)
{
	close(fd[1]);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, status, 0);
}

int	heredoc(t_shell *mish, const char *delim, bool ex)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		give_heredoc_signals();
		close(fd[0]);
		help_heredic(NULL, delim, fd);
		close(fd[1]);
		free_and_exit(mish, 0);
	}
	give_heredoc_signals();
	helper(fd, pid, &status);
	if (heredoc_helper(mish, status, fd, ex))
		return (-1);
	return (fd[0]);
}
