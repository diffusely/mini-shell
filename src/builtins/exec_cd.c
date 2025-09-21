/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:35:24 by vmakarya          #+#    #+#             */
/*   Updated: 2025/09/16 17:04:02 by vmakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool	find_list(const char *input, t_list **envp_list)
{
	t_list	*curr;
	int		place;

	curr = *envp_list;
	while (curr)
	{
		if (curr->content && ft_strchr(curr->content, '='))
		{
			place = find_word_place(curr->content);
			if (ft_strncmp(curr->content, input, place) == 0)
				return (true);
		}
		curr = curr->next;
	}
	return (false);
}

bool check_arguments_count(char **input)
{
	int i;

	i = 0;
	while (input[i])
		i++;
	if (i > 2)
		return (true);
	return (false);
}

int	exec_cd(char **input, t_list **envp_list, int i)
{
	char *res;

	if(check_arguments_count(input))
		return (printf("cd: too many arguments \n"), 1);
	if(i % 2 != 0)
		return (printf("cd: no such file or directory: %s\n", input[1]), 1);
	res = input[1]; 
	if (!res)
	{
		if (find_list("HOME", envp_list) && chdir(getenv("HOME")) == 0)
			return (0);
		return (0);
	}
	if (chdir(res) == 0)
		return (0);
	ft_err("cd: no such file or directory: ");
	ft_err(res);
	ft_err("\n");
	return (127);
}
