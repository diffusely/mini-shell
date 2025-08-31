/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:39:23 by vmakarya          #+#    #+#             */
/*   Updated: 2025/08/31 16:00:53 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_env(t_list *env)
{
	while (env)
	{
		if (env->content)
			printf("%s\n", (char *)env->content);
		env = env->next;
	}
}

bool	exec_env(char *input, t_list **list_env)
{
	(void)list_env;
	printf("%s\n", input);
	input += 3;
	printf("%s\n", input);
	while (*input && ft_isspace(*input))
		input++;
	
	if (*input != '\0')
	{
		ft_err("env: too many arguments\n");
		return (true);
	}
	print_env(*list_env);	
	return (true);
}
