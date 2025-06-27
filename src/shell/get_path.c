/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:29:20 by noavetis          #+#    #+#             */
/*   Updated: 2025/06/27 19:30:39 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*helper(char **path, char *cmd)
{
	char	*res;
	int		i;
	int		j;

	j = 0;
	i = -1;
	while (cmd[j])
	{
		if (cmd[j] == '.' && cmd[j + 1] == '.')
			return (free_split(path), ft_strdup("Error"));
		++j;
	}
	while (path[++i])
	{
		res = ft_strdup(cmd);
		if (access(res, X_OK) == 0)
			return (free_split(path), res);
		free(res);
	}
	return (free_split(path), ft_strdup("Error"));
}

static char	*find_path(t_pip *pip, char **path, char *cmd)
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
			free_split(path);
			free_all(pip);
			error_handle("*JOIN* Bad alloc", 1);
		}
		if (access(res, X_OK) == 0)
			return (free_split(path), res);
		free(res);
	}
	return (free_split(path), ft_strdup("Error"));
}

char	*get_path(t_pip *pip, char *cmd)
{
	char	**path;
	int		i;

	i = -1;
	path = NULL;
	if (!cmd)
		return (ft_strdup("Error"));
	while (pip->envp[++i])
	{
		if (!ft_strncmp(pip->envp[i], "PATH=", 5))
		{
			path = ft_split(pip->envp[i] + 5, ':');
			break ;
		}
	}
	if (!path)
		return (NULL);
	return (find_path(pip, path, cmd));
}
