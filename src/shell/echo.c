/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:20:25 by vmakarya          #+#    #+#             */
/*   Updated: 2025/08/13 14:33:56 by vmakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static bool check(char *input, int *new_line)
{
	new_line = false;
	while (*input && ft_isspace(*input))
		input++;
	if (ft_strncmp(*input, "echo", 5) == 0)
	{
		input += 4;
		while (*input && ft_isspace(*input))
			input++;
		if(ft_strncmp(*input, "-n", 2) == 0)
			new_line = true;
		return (true);
	}
	else
		return (false);
}

void exec_echo(char *input, t_list **list_env)
{
	bool new_line;

	if(!check(input, &new_line))
		return ;
	
	
}