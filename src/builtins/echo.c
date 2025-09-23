/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:20:25 by vmakarya          #+#    #+#             */
/*   Updated: 2025/09/24 01:58:44 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

static void	print_arg(char *arg)
{
	if (!arg)
		return ;

	printf("%s", arg);
}

int	exec_echo(char **cmd, t_list **envp, t_shell **mish)
{
	bool	new_line;
	int		i;
	int		j;

	(void)envp;
	(void)mish;
	i = 1;
	new_line = true;
	while (cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n')
	{
		j = 1;
		while (cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] != '\0')
			break;
		new_line = false;
		i++;
	}
	while (cmd[i])
	{
		print_arg(cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	return (0);
}
