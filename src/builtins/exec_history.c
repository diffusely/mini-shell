/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 00:23:21 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/22 02:14:55 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

int	exec_history(t_shell *mish, char **cmd)
{
	if (!valid_cmd(cmd[1]))
	{
		ft_err("minishell: history: ");
		ft_err(cmd[1]);
		ft_err(": numeric argument required\n");
		return (1);
	}
	print_history(mish);
	return (0);
}

void	exec_exit(char **cmd, t_shell *mish)
{
	ft_putstr_fd("exit\n", 1);
	if (!valid_cmd(cmd[1]))
	{
		ft_err("minishell: exit: ");
		ft_err(cmd[1]);
		ft_err(": numeric argument required\n");
		free_all(mish);
		exit(2);
	}
	free_all(mish);
	exit(0);
}
