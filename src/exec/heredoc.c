/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 01:43:04 by noavetis          #+#    #+#             */
/*   Updated: 2025/10/18 23:55:08 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	ctrl_d_message(char *delim, int l_count)
{
	delim = expand(delim, NULL);
	ft_err("minishell: ");
	ft_err("warning: ");
	ft_err("here-document at line ");
	ft_putnbr_fd(l_count, 2);
	ft_err(" delimited by end-of-file");
	ft_err("(wanted `");
	ft_err((char *)delim);
	ft_err("')\n");
	free(delim);
}

void	fake_heredoc(const char *delim, int l_count)
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
				if (!line)
					ctrl_d_message(ft_strdup(delim), l_count);
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

static void	help_heredoc(char *line, char *delim, int *fd, t_shell *mish)
{
	bool	op;

	if (strchr(delim, '"') || strchr(delim, '\''))
		op = false;
	else
		op = true;
	while (1)
	{
		line = readline("> ");
		if (line && op)
			line = expand(line, mish);
		if (!line || ft_strcmp(line, delim) == 0)
		{
			if (!line)
				ctrl_d_message(ft_strdup(delim), mish->l_count);
			free(line);
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

int	heredoc(t_shell *mish, char *delim, bool ex)
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
		help_heredoc(NULL, delim, fd, mish);
		close(fd[1]);
		free_and_exit(mish, 0);
	}
	give_heredoc_signals();
	helper(fd, pid, &status);
	if (heredoc_helper(mish, status, fd, ex))
		return (-1);
	return (fd[0]);
}
