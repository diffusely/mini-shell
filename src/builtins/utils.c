/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 21:27:14 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/01 16:42:22 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	find_word_place(char *word)
{
	int	i;

	i = 0;
	while (word && word[i] && word[i] != '=')
		++i;
	return (i);
}

bool	check_builtins(char **cmd, t_list **envp)
{
	char	*tmp;

	if (!cmd || !cmd[0] || !cmd[0][0])
		return (false);
	tmp = *cmd;
	while (*tmp && is_quoted(*tmp))
		tmp++;
	if (*tmp == ' ')
		return (false);
	// if (!ft_strncmp(*cmd, "echo", 4))
	// 	return (exec_echo(tmp, envp));
	if (tmp[1] && !ft_strncmp(tmp, "cd", 2))
		return (exec_cd(cmd[1], envp));
	else if (!ft_strncmp(tmp, "pwd", 3))
		return (exec_pwd(tmp));
	else if (!ft_strncmp(tmp, "export", 6))
		return (true);
	else if (!ft_strncmp(tmp, "unset", 5))
		return (true);
	else if (!ft_strncmp(tmp, "env", 3))
		return (exec_env(tmp ,envp));
	else if (!ft_strncmp(tmp, "exit", 4))
		return (true);
	return (false);
}
