/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:35:24 by vmakarya          #+#    #+#             */
/*   Updated: 2025/10/12 14:39:27 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

static void	change_type(char *input, char *old, t_list *curr, bool f)
{
	if (ft_strncmp(curr->content, "OLDPWD=", 7) == 0)
	{
		if (!old)
		{
			*(char *)(curr->content + 7) = '\0';
			return ;
		}
		free(curr->content);
		curr->content = ft_calloc(1, ft_strlen(old) + 8);
		ft_strcpy(curr->content, "OLDPWD=");
		ft_strcpy(curr->content + 7, old);
	}
	else if (ft_strncmp(curr->content, "PWD=", 4) == 0)
	{
		if (f)
		{
			helper_cd(curr, input, old);
			return ;
		}
		free(curr->content);
		curr->content = ft_calloc(1, ft_strlen(input) + 5);
		ft_strcpy(curr->content, "PWD=");
		ft_strcpy(curr->content + 4, input);
	}
}

//  mkdir -p a/b/c && cd a/b/c/ && rm -rf ../../../a
static void	find_change(char *input, char *old, t_list **envp_list, bool f)
{
	t_list	*curr;

	if (!envp_list)
		return ;
	curr = *envp_list;
	while (curr)
	{
		if (curr->content && ft_strchr(curr->content, '='))
			change_type(input, old, curr, f);
		curr = curr->next;
	}
}

bool	check_arguments_count(char **input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	if (i > 2)
		return (true);
	return (false);
}

static int	change_dir(char *res, char *old, t_list **envp_list)
{
	char	*cwd;

	if (!res)
	{
		res = find_list("HOME", envp_list);
		if (!res)
			return (ft_err("minishell: cd: HOME not set\n"), 1);
	}
	if (chdir(res) == 0)
	{
		cwd = getcwd(NULL, 0);
		if (cwd)
			find_change(cwd, old, envp_list, 0);
		else
			find_change(res, old, envp_list, 1);
		if (cwd)
			free(cwd);
		else
		{
			ft_err("cd: error retrieving current directory:");
			perror(" getcwd: cannot access parent directories: ");
		}
		return (0);
	}
	return (ft_err_msg("minishell: cd: ", res), 1);
}

int	exec_cd(char **input, t_list **envp_list, int i)
{
	char	*old;

	old = find_list("PWD", envp_list);
	if (check_arguments_count(input))
		return (ft_err("minishell: cd: too many arguments\n"), 1);
	if (i % 2 != 0)
		return (ft_err_msg("minishell: cd: ", input[1]), 1);
	return (change_dir(input[1], old, envp_list));
}
