/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:39:23 by vmakarya          #+#    #+#             */
/*   Updated: 2025/09/22 16:09:19 by vmakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

void	print_env(t_list *env)
{
	while (env)
	{
		if (env->content)
			printf("%s\n", (char *)env->content);
		env = env->next;
	}
}

bool	exec_env(char *input, t_list **list_env, t_shell **mish)
{
	if (input)
	{
		ft_err("minishell: env: too many arguments\n");
		(*mish)->status = 127;
		return (1);
	}
	(*mish)->status = 0;
	print_env(*list_env);
	return (0);
}
