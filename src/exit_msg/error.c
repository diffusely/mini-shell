/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:37:14 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/13 19:49:53 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "message.h"

void	error_print(const char *cmd, const char *msg, int flag)
{
	printf("%s: %s", cmd, msg);
	if (flag)
		perror(msg);
	exit(EXIT_FAILURE);
}

void	error_handle(char *msg, int flag)
{
	if (flag)
		ft_putstr_fd(msg, 2);
	else
		perror(msg);
	exit(EXIT_FAILURE);
}

void	ft_err(char *msg)
{
	ft_putstr_fd(msg, 2);
}

void	error_exit_msg(t_shell *mish, t_ast *left, char *msg)
{
	if (left->cmd[0] && left->cmd[0][0])
		ft_err(left->cmd[0]);
	free_all(mish);
	error_handle(msg, 1);
}

void	free_exit_msg(t_shell *mish, char *msg)
{
	free_all(mish);
	error_handle(msg, 0);
}
