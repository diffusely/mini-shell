/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:54:24 by noavetis          #+#    #+#             */
/*   Updated: 2025/10/11 21:31:26 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

void	free_split(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		free(str[i++]);
	free(str);
	str = NULL;
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_signal = 130;
	}
	else if (sig == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 20);
		g_signal = 131;
	}
}

static void	fd_error(t_shell *mish, t_redir *r, bool flag)
{
	ft_err("minishell: ");
	if (r->filename)
		perror(r->filename);
	if (flag)
	{
		free_all(mish);
		exit(1);
	}
}

static int	helper(t_shell *mish, t_redir *r, int *fd, bool ex)
{
	if (r->type == R_OUT)
		*fd = open(r->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (r->type == R_APPEND)
		*fd = open(r->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (r->type == R_IN)
		*fd = open(r->filename, O_RDONLY);
	else if (r->type == R_HEREDOC)
	{
		*fd = heredoc(mish, r->filename, ex);
		if (*fd == -1)
			return (1);
		if (r->next && r->next->type == R_HEREDOC)
			close(*fd);
	}
	return (0);
}

int	create_files(t_shell *mish, t_redir *r, bool ex)
{
	int	fd;

	while (r)
	{
		if (helper(mish, r, &fd, ex))
			return (130);
		if (fd < 0)
		{
			if (is_built(mish->tree->cmd))
				fd_error(mish, r, 0);
			else
				fd_error(mish, r, 1);
			return (1);
		}
		if (r->type == R_OUT || r->type == R_APPEND)
			dup2(fd, STDOUT_FILENO);
		else
			dup2(fd, STDIN_FILENO);
		close(fd);
		r = r->next;
	}
	return (0);
}
