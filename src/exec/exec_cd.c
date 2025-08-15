/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:35:24 by vmakarya          #+#    #+#             */
/*   Updated: 2025/08/15 19:48:02 by vmakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static bool find_list(const char* input, t_list **envp_list)
{
	t_list *curr;

	curr = *envp_list;	
	while (curr)
	{
		if (curr->content && ft_strchr(curr->content, '=')) 
		{
			int place = find_word_place(curr->content);
			if (ft_strncmp(curr->content, input, place) == 0)
				return (true);
		}
		curr = curr->next;
	}
	return (false);
}

bool	exec_cd(const char *input, t_list **envp_list)
{
	while (*input && ft_isspace(*input))
		input++;
  	if (ft_strncmp(input, "cd", 2) == 0 && (input[2] == '\0' || ft_isspace(input[2])))
        input += 2;
	else
		return (true);
	while (*input && ft_isspace(*input))
		input++;
	if (!(*input))
	{
		if(find_list("HOME", envp_list) && chdir(getenv("HOME")) == 0)
				return (true);
		printf("stex el hasav\n");
		return (true);
	}
	if (chdir(input) == 0)
		return (true);
	printf("cd: no such file or directory: %s\n", input);
	return (true);
}
