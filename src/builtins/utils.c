/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 21:27:14 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/30 22:15:06 by noavetis         ###   ########.fr       */
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

bool	check_builtins(char *cmd, t_list **envp)
{
	while (cmd && *cmd && ft_isspace(*cmd))
		cmd++;
	if (!ft_strncmp(cmd, "echo", 4))
		return (exec_echo(cmd, envp));
	else if (!ft_strncmp(cmd, "cd", 2))
		return (exec_cd(cmd, envp));
	else if (!ft_strncmp(cmd, "pwd", 3))
		return (exec_pwd(cmd));
	else if (!ft_strncmp(cmd, "export", 6))
		return (true);
	else if (!ft_strncmp(cmd, "unset", 5))
		return (true);
	else if (!ft_strncmp(cmd, "env", 3))
		return (exec_env(cmd ,envp));
	else if (!ft_strncmp(cmd, "exit", 4))
		return (true);
	return (false);
}
