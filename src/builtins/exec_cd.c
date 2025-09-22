/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:35:24 by vmakarya          #+#    #+#             */
/*   Updated: 2025/09/22 17:13:31 by vmakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

static void	change_type(char *input, char *old, t_list *curr)
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
		free(curr->content);
		curr->content = ft_calloc(1, ft_strlen(input) + 5);
		ft_strcpy(curr->content, "PWD=");
		ft_strcpy(curr->content + 4, input);
	}
}

static void	find_change(char *input, char *old, t_list **envp_list)
{
	t_list	*curr;

	if (!envp_list)
		return ;
	curr = *envp_list;
	while (curr)
	{
		if (curr->content && ft_strchr(curr->content, '='))
			change_type(input, old, curr);
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

// bool	exec_cd(t_shell *shell, char **input, t_list **envp_list, int i)
// {
// 	char	*res;
// 	char	*old;

// 	if (check_arguments_count(input))
// 	{
// 		shell->status = 2;
// 		return (ft_err("cd: too many arguments \n"), 1);
// 	}
// 	if (i % 2 != 0)
// 	{
// 		shell->status = 1;
// 		ft_err_msg("cd: no such file or directory: ", input[1]);
// 		return (true);
// 	}
// 	res = input[1];
// 	old = find_list("PWD", envp_list);
// 	if (!res)
// 	{
// 		res = find_list("HOME", envp_list);
// 		if (res && chdir(res) == 0)
// 		{
// 			shell->status = 0;
// 			find_change(res, old, envp_list);
// 			return (refresh_env_matrix(&shell), 0);
// 		}
// 		if (!res)
// 		{
// 			shell->status = 1;
// 			return (ft_err("minishell: cd: HOME not set\n"), 1);
// 		}
// 	}
// 	else if (chdir(res) == 0)
// 	{
// 		res = getcwd(NULL, 0);
// 		find_change(res, old, envp_list);
// 		if (res)
// 			free(res);
// 		shell->status = 0;
// 		return (refresh_env_matrix(&shell), 0);
// 	}
// 	ft_err_msg("cd: no such file or directory: ", res);
// 	shell->status = 1;
// 	return (true);
// }


static bool	change_dir(t_shell *shell, char *res, char *old, t_list **envp_list)
{
	if (!res)
	{
		res = find_list("HOME", envp_list);
		if (!res)
		{
			shell->status = 1;
			return (ft_err("minishell: cd: HOME not set\n"), 1);
		}
	}
	if (chdir(res) == 0)
	{
		char *cwd = getcwd(NULL, 0);
		find_change(cwd ? cwd : res, old, envp_list);
		if (cwd)
			free(cwd);
		shell->status = 0;
		return (refresh_env_matrix(&shell), 0);
	}
	ft_err_msg("cd: no such file or directory: ", res);
	shell->status = 1;
	return (1);
}

bool	exec_cd(t_shell *shell, char **input, t_list **envp_list, int i)
{
	char *old = find_list("PWD", envp_list);

	if (check_arguments_count(input))
	{
		shell->status = 2;
		ft_err("cd: too many arguments \n");
		return (true);
	}
	if (i % 2 != 0)
		return (shell->status = 1, ft_err_msg("cd: no such file or directory: ", input[1]), 1);
	return (change_dir(shell, input[1], old, envp_list));
}
