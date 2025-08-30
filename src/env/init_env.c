/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:49:39 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/30 20:11:10 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	print_env_matrix(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		++i;
	}
}

char	**init_env_matrix(t_list *env)
{
	char	**res;
	int		len;
	int		i;

	if (!env)
		return (NULL);
	len = ft_lstsize(env);
	res = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = env->content;
		env = env->next;
		++i;
	}
	res[i] = NULL;
	return (res);
}

void	refresh_env_matrix(t_shell **shell)
{
	if ((*shell)->env)
		free((*shell)->env);
	(*shell)->env = init_env_matrix((*shell)->list_env);
}
