/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:35:24 by vmakarya          #+#    #+#             */
/*   Updated: 2025/08/13 18:04:29 by vmakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

bool	exec_cd(const char *input, t_list **envp_list)
{
	
	while (*input && ft_isspace(*input))
		input++;
	if (ft_strncmp(input, "cd", 2) == 0)
		input += 2;
	else
		return (true);
	while (*input && ft_isspace(*input))
		input++;
	if (!(*input))
	  {
		if(!find_list("HOME", envp_list) && chdir(getenv("HOME")) == 0)
				return (true);
		else
			return (printf("%s\n", "chka Home dir"), true);
	  }
	if (!find_list(input, envp_list) && chdir(input) == 0)
		return (true);
	printf("cd: no such file or directory: %s\n", input);
	return (false);
}