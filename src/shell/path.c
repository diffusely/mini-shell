/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:29:20 by noavetis          #+#    #+#             */
/*   Updated: 2025/10/12 18:33:12 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*helper(char **path, char *cmd)
{
	int		j;

	j = 0;
	while (cmd[j])
	{
		if (cmd[j] == '.' && cmd[j + 1] == '.')
			return (free_split(path), ft_strdup("Error"));
		++j;
	}
	return (free_split(path), ft_strdup(cmd));
}

static char	*find_path(t_shell *mish, char **path, char *cmd)
{
	char	*res;
	int		i;

	i = -1;
	if (!ft_strncmp("./", cmd, 2) || !ft_strncmp("/", cmd, 1))
		return (helper(path, cmd));
	while (path[++i])
	{
		res = ft_strjoin(path[i], "/");
		res = ft_strjoin_free(res, cmd);
		if (!res)
		{
			free_all(mish);
			free_split(path);
			error_handle("*JOIN* Bad alloc", 1);
		}
		if (access(res, X_OK) == 0)
			return (free_split(path), res);
		free(res);
	}
	return (free_split(path), ft_strdup("Error"));
}

char	*get_path(t_shell *mish, char *cmd)
{
	char	**path;
	t_list	*tmp;

	path = NULL;
	if (!cmd)
		return (ft_strdup("Error"));
	tmp = mish->list_env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "PATH=", 5))
		{
			path = ft_split(tmp->content + 5, ':');
			break ;
		}
		tmp = tmp->next;
	}
	if (!path)
		return (NULL);
	return (find_path(mish, path, cmd));
}
