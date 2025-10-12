/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:20:25 by vmakarya          #+#    #+#             */
/*   Updated: 2025/10/12 14:36:50 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

static void	print_arg(char *arg)
{
	if (!arg)
		return ;
	printf("%s", arg);
}

static void	helper(char **cmd, int i)
{
	while (cmd[i])
	{
		print_arg(cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
}

int	exec_echo(char **cmd)
{
	bool	new_line;
	int		i;
	int		j;

	i = 1;
	new_line = true;
	while (cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n')
	{
		j = 1;
		while (cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] != '\0')
			break ;
		new_line = false;
		i++;
	}
	helper(cmd, i);
	if (new_line)
		printf("\n");
	return (0);
}

void	helper_cd(t_list *curr, char *input, char *old)
{
	char	*res;

	res = ft_strjoin_free2(old, ft_strdup("/"));
	res = ft_strjoin_free(res, input);
	free(curr->content);
	curr->content = ft_calloc(1, ft_strlen(res) + 5);
	ft_strcpy(curr->content, "PWD=");
	ft_strcpy(curr->content + 4, res);
	free(res);
}
