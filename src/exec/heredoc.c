/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 01:43:04 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/14 21:57:20 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	heredoc(const char *delim)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		// signal(SIGINT, sigint_heredoc);
		// signal(SIGQUIT, SIG_IGN);  
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
	signal(SIGINT, SIG_IGN);
	close(fd[1]);
	close(fd[0]);
	return (0);
}
