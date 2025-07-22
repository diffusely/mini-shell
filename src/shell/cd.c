/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:31:02 by vmakarya          #+#    #+#             */
/*   Updated: 2025/07/22 18:55:04 by vmakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int exec_cd(const char *input)
{
	while (*input && ft_isspace(*input))
		input++;
	if (!ft_strncmp(input, "cd", 2))
		input += 2;
	else 
		return (false);
	while (*input && ft_isspace(*input))
		input++;
	if (!(*input))
	{
		if (chdir(getenv("HOME")) == 0)
			return (true);
	}
	if (chdir(input) == 0)
		return (true);
	printf("cd: no such file or directory: %s\n", input);
	return (false);
} 
