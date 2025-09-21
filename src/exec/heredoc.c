/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 01:43:04 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/21 19:35:43 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	fake_heredoc(const char *delim)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		free(line);
	}
}

void	help_heredic(char *line, const char *delim, int *fd)
{
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
}

int	heredoc(t_shell *mish, const char *delim)
{
	int		fd[2];
	pid_t	pid;
	char	*line;

	line = NULL;
	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		close(fd[0]);
		help_heredic(line, delim, fd);
		close(fd[1]);
		free_all(mish);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	return (close(fd[1]), fd[0]);
}
