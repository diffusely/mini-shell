/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:06:18 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/07 00:02:55 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_and_exit(t_shell *mish, int status)
{
	free_all(mish);
	exit(status);
}

void	dup_and_close(int fd[2], int new_fd, int close_read)
{
	if (close_read)
	{
		close(fd[1]);
		dup2(fd[0], new_fd);
		close(fd[0]);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], new_fd);
		close(fd[1]);
	}
}
