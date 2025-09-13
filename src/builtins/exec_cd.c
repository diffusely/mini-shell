/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:35:24 by vmakarya          #+#    #+#             */
/*   Updated: 2025/09/13 17:07:16 by vmakarya         ###   ########.fr       */
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

bool	exec_cd(char *input, t_list **envp_list)
{
	int	i;

	if (!input)
	{
		if (find_list("HOME", envp_list) && chdir(getenv("HOME")) == 0)
			return (true);
		return (true);
	}
	while (*input && is_quoted(*input))
		++input;
	i = 0;
	while (input[i] && !is_quoted(input[i]))
		++i;
	if (input[i])
		input[i] = '\0';
	if (chdir(input) == 0)
		return (true);
	ft_err("cd: no such file or directory: ");
	ft_err((char *)input);
	ft_err("\n");
	return (true);
}
