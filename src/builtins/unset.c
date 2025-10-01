/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:52:54 by vmakarya          #+#    #+#             */
/*   Updated: 2025/10/01 22:55:09 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

void	find_remove(const char *input, t_list **envp_list)
{
	t_list	*curr;
	t_list	*prev;

	if (!envp_list || !*envp_list)
		return ;
	prev = NULL;
	curr = *envp_list;
	while (curr)
	{
		if (curr->content && ft_strchr(curr->content, '='))
		{
			if (ft_strncmp(curr->content, input, f_w_p(curr->content)) == 0)
			{
				if (!prev)
					*envp_list = curr->next;
				else
					prev->next = curr->next;
				free(curr->content);
				free(curr);
				return ;
			}
		}
		prev = curr;
		curr = curr->next;
	}
}

int	exec_unset(char **cmd, t_list **envp)
{
	int		i;

	if (!cmd || !*cmd)
		return (1);
	i = 1;
	while (cmd[i])
	{
		find_remove(cmd[i], envp);
		i++;
	}
	return (0);
}
