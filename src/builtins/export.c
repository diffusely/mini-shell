/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 23:08:24 by vmakarya          #+#    #+#             */
/*   Updated: 2025/09/24 00:15:58 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

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

static bool	valid_identifier(const char *s)
{
	int	i;

	if (!s || !(ft_isalpha(*s) || *s == '_'))
		return (false);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (false);
		++i;
	}
	return (true);
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

int	exec_export(char **cmd, t_list **envp_list)
{
	t_list	*tmp;
	int		i;
	int		j;

	tmp = *envp_list;
	i = 1;
	if (!valid_identifier(cmd[i]))
	{
		ft_err("minishell: export: ");
		ft_err(cmd[1]);
		ft_err(": not a valid identifier");
		return (1);
	}
	if (print_export(cmd, tmp, i))
		return (0);
	while (cmd[i])
	{
		j = 0;
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
	return (0);
}
