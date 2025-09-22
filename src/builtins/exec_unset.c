/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:52:54 by vmakarya          #+#    #+#             */
/*   Updated: 2025/09/22 15:25:31 by vmakarya         ###   ########.fr       */
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

bool	exec_unset(t_shell *mish, char **cmd, t_list **envp)
{
	int		i;

	if (!cmd || !*cmd)
		return (false);
	i = 1;
	while (cmd[i])
	{
		cmd[i] = remove_quotes(cmd[i]);
		find_remove(cmd[i], envp);
		i++;
	}
	refresh_env_matrix(&mish);
	mish->status = 0;
	return (true);
}
