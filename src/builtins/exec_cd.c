/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:35:24 by vmakarya          #+#    #+#             */
/*   Updated: 2025/09/21 22:04:06 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool	find_list(const char *input, t_list **envp_list)
{
	t_list	*curr;
	int		place;

	curr = *envp_list;
	while (curr)
	{
		if (curr->content && ft_strchr(curr->content, '='))
		{
			place = f_w_p(curr->content);
			if (ft_strncmp(curr->content, input, place) == 0)
				return (true);
		}
		curr = curr->next;
	}
	return (false);
}

static void	find_change(char *input, t_list **envp_list)
{
	t_list	*curr;

	if (!envp_list || !*envp_list)
		return ;
	curr = *envp_list;
	while (curr)
	{
		if (curr->content && ft_strchr(curr->content, '='))
		{
			if (ft_strncmp(curr->content, "PWD=", 4) == 0)
			{
				char *new_pwd = malloc(ft_strlen(input) + 5);
				if (!new_pwd)
    				return;

				ft_strcpy(new_pwd, "PWD=");
				strcat(new_pwd, input);

				char *old = curr->content;
				printf("%s\n", old);
				curr->content = new_pwd;
				if (old)
    				free(old);
				free(input);
				return ;
			}
		}
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

int	exec_cd(t_shell **shell, char **input, t_list **envp_list, int i)
{
	char	*res;

	if (check_arguments_count(input))
		return (ft_err("cd: too many arguments \n"), 1);
	if (i % 2 != 0)
	{
		ft_err_msg("cd: no such file or directory: ", input[1]);
		return (1);
	}
	res = input[1];
	if (!res)
	{
		if (find_list("HOME", envp_list) && chdir(getenv("HOME")) == 0)
			return (find_change(getenv("HOME"), envp_list), 0);
		return (ft_err("minishell: cd: HOME not set\n"), 1);
	}
	if (chdir(res) == 0)
	{
		find_change(getcwd(NULL, 0), envp_list);
		refresh_env_matrix(shell);
		return (0);
	}
	ft_err_msg("cd: no such file or directory: ", res);
	return (127);
}
