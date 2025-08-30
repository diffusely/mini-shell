/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:39:23 by vmakarya          #+#    #+#             */
/*   Updated: 2025/08/30 22:05:11 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

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
	input += 3;
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
