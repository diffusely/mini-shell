/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 23:08:24 by vmakarya          #+#    #+#             */
/*   Updated: 2025/09/21 16:20:26 by vmakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "shell.h"
# include "message.h"

#include <stdlib.h>
#include <string.h>

void push_back(const char *cmd, t_list **envp_list)
{
    t_list *new_node;
    t_list *tmp;

	new_node = malloc(sizeof(t_list));
    if (!new_node)
        return;
    new_node->content = strdup(cmd);
    if (!new_node->content) {
        free(new_node);
        return ;
    }
    new_node->next = NULL;
    if (*envp_list == NULL) {
        *envp_list = new_node;
        return ;
    }
    tmp = *envp_list;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
}

bool exec_export(char **cmd, t_list **envp_list)
{
	int		i;
	int		j;
	t_list	*tmp;

	tmp = *envp_list;
	i = 1;
	j = 0;
	if (!cmd[i])
	{
		while(tmp)
		{
			printf("declare -x %s\n", (char*)tmp->content);
			tmp = tmp->next;
		}
		return (true);
	}
	while (cmd[i])
	{
		cmd[i] = remove_quotes(cmd[i]);
		while (cmd[i][j])
		{
			if(cmd[i][j] == '=')
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
