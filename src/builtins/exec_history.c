/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 00:23:21 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/07 01:14:02 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	exec_history(char **cmd)
{
	if (!valid_cmd(cmd[1]))
	{
		ft_err("minishell: history: ");
		ft_err(cmd[1]);
		ft_err(": numeric argument required\n");
		return (1);
	}
	print_history();
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
		exit(2);
	}
	free_all(mish);
	exit(0);
}
