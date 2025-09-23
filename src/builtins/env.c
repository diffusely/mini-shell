/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:39:23 by vmakarya          #+#    #+#             */
/*   Updated: 2025/09/24 00:01:17 by noavetis         ###   ########.fr       */
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

t_list	*init_env(char **envp)
{
	int		i;
	char	*copy;
	t_list	*list_env;
	t_list	*node;

	list_env = NULL;
	i = 0;
	if (list_env == NULL)
	{
		while (envp && envp[i])
		{
			copy = ft_calloc(1, ft_strlen(envp[i]) + 1);
			if (!copy)
				return (NULL);
			ft_strcpy(copy, envp[i]);
			node = ft_lstnew(copy);
			if (!node)
				return (free(copy), NULL);
			ft_lstadd_back(&list_env, node);
			++i;
		}
	}
	return (list_env);
}

void	refresh_env_matrix(t_shell **shell)
{
	if ((*shell)->env)
		free((*shell)->env);
	(*shell)->env = init_env_matrix((*shell)->list_env);
}
