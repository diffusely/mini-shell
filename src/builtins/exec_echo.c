/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:20:25 by vmakarya          #+#    #+#             */
/*   Updated: 2025/09/22 16:35:09 by vmakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

static char	*find_lst(const char *input, t_list **envp_list)
{
	t_list	*curr;
	int		place;
	char	*content;
	int		i;

	curr = *envp_list;
	i = 0;
	while (curr)
	{
		if (curr->content && ft_strchr(curr->content, '='))
		{
			content = (char *)curr->content;
			place = f_w_p(curr->content);
			if (ft_strncmp(content, input, place) == 0)
			{
				while (content[i] != '=')
					i++;
				return (content + i + 1);
			}
		}
		curr = curr->next;
	}
	return (NULL);
}

static void	check_dollar(char *input, t_list **list_env, bool new_line)
{
	char	*cmd;

	input++;
	cmd = find_lst(input, list_env);
	if (cmd)
		printf("%s", cmd);
	if (new_line)
		printf("\n");
}

char	*remove_quotes(char *str)
{
	char	*src;
	char	*dst;

	src = str;
	dst = str;
	if (!str)
		return (NULL);
	while (*src)
	{
		if (*src != '\'' && *src != '"')
			*dst++ = *src;
		src++;
	}
	*dst = '\0';
	return (str);
}

static void	print_arg(char *arg, t_list **envp, t_shell **mish)
{
	if (!arg)
		return ;
	(void)mish;
	arg = remove_quotes(arg);
	if (!ft_strcmp(arg, "$?"))
		printf("%d", (*mish)->status);
	else if (arg && arg[0] == '$')
		check_dollar(arg, envp, false);
	else
		printf("%s", arg);
}

bool	exec_echo(char **cmd, t_list **envp, t_shell **mish)
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
			break;
		new_line = false;
		i++;
	}
	while (cmd[i])
	{
		print_arg(cmd[i], envp, mish);
		if (cmd[i + 1]) printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	return (true);
}
