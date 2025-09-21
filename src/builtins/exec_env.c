/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:39:23 by vmakarya          #+#    #+#             */
/*   Updated: 2025/09/16 17:06:24 by vmakarya         ###   ########.fr       */
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

int	exec_env(char *input, t_list **list_env)
{
	if (input)
	{
		ft_err("minishell: env: too many arguments\n");
		return (127);
	}
	print_env(*list_env);
	return (0);
}
