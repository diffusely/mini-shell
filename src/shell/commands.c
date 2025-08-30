/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:19:55 by vmakarya          #+#    #+#             */
/*   Updated: 2025/08/30 22:18:04 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool	remove_list(const char *input, t_list **envp_list)
{
	t_list	*curr;
	t_list	*prev;

	curr = *envp_list;
	prev = NULL;
	while (curr)
	{
		if (curr->content && ft_strchr(curr->content, '='))
		{
			int place = find_word_place(curr->content);
			if (ft_strncmp(curr->content, input, place) == 0)
			{
				if (prev == NULL)
					*envp_list = curr->next;
				else
					prev->next = curr->next;
				free(curr->content);
				free(curr);
				return (true);
			}
		}
		prev = curr;
		curr = curr->next;
	}
	return (false);
}

bool check_unset(char *input, t_list **env_list)
{
	while (*input && ft_isspace(*input))
		input++;
	if (ft_strncmp(input, "unset", 5) == 0)
		input += 5;
	else
		return (true);
	while (*input && ft_isspace(*input))
		input++;
	remove_list(input, env_list);
	return (true);
}

t_list* init_env(char **envp)
{
	int	i;
	char *copy;
	t_list *list_env;
	 
	list_env = NULL;
	i = 0;
	if (list_env == NULL)
	{
		while (envp && envp[++i])
		{
			copy = ft_calloc(1, ft_strlen(envp[i]) + 1);
			if (!copy)
				return (NULL);
			ft_strcpy(copy, envp[i]);
			t_list *node = ft_lstnew(copy);
			if (!node)
			{
				free(copy);
				return (NULL);
			}
			ft_lstadd_back(&list_env, node);
		}
	}
	return (list_env);
}
