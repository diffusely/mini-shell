/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 23:08:24 by vmakarya          #+#    #+#             */
/*   Updated: 2025/09/21 19:35:07 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	push_back(const char *cmd, t_list **envp_list)
{
	t_list	*new_node;
	t_list	*tmp;

	new_node = ft_calloc(1, sizeof(t_list));
	if (!new_node)
		return ;
	new_node->content = ft_strdup(cmd);
	if (!new_node->content)
	{
		free(new_node);
		return ;
	}
	new_node->next = NULL;
	if (*envp_list == NULL)
	{
		*envp_list = new_node;
		return ;
	}
	tmp = *envp_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

static bool	print_export(char **cmd, t_list	*tmp, int i)
{
	if (!cmd[i])
	{
		while (tmp)
		{
			printf("declare -x %s\n", (char *)tmp->content);
			tmp = tmp->next;
		}
		return (true);
	}
	return (false);
}

bool	exec_export(char **cmd, t_list **envp_list)
{
	t_list	*tmp;
	int		i;
	int		j;

	tmp = *envp_list;
	i = 1;
	j = 0;
	if (print_export(cmd, tmp, i))
		return (true);
	while (cmd[i])
	{
		cmd[i] = remove_quotes(cmd[i]);
		while (cmd[i][j])
		{
			if (cmd[i][j] == '=')
			{
				find_remove(cmd[i], envp_list);
				push_back(cmd[i], envp_list);
				break ;
			}
			j++;
		}
		i++;
	}
	return (true);
}
