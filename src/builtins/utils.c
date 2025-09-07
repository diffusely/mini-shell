/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 21:27:14 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/08 01:25:13 by noavetis         ###   ########.fr       */
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

int	is_built(char **cmd)
{
	char	*tmp;

	if (!cmd || !cmd[0] || !cmd[0][0])
		return (NONE);
	tmp = *cmd;
	if (ft_strncmp(tmp, "echo", 4) == 0)
		return (ECHO);
	if (ft_strncmp(tmp, "cd", 2) == 0)
		return (CD);
	else if (ft_strcmp(tmp, "pwd") == 0)
		return (PWD);
	else if (ft_strncmp(tmp, "export", 6) == 0)
		return (EXPORT);
	else if (ft_strncmp(tmp, "unset", 5) == 0)
		return (UNSET);
	else if (ft_strcmp(tmp, "env") == 0)
		return (ENV);
	else if (ft_strcmp(tmp, "exit") == 0)
		return (EXIT);
	else if (ft_strcmp(tmp, "history") == 0)
		return (HISTORY);
	return (NONE);
}

int	exec_built(char **cmd, t_list **envp, t_shell *mish)
{
	int		type;
	char	*tmp;

	tmp = *cmd;
	type = is_built(cmd);
	if (type == ECHO)
		return (exec_echo(tmp, envp));
	else if (type == CD)
		return (exec_cd(cmd[1], envp));
	else if (type == PWD)
		return (exec_pwd(tmp));
	else if (type == EXPORT)
		return (0);
	else if (type == UNSET)
		return (0);
	else if (type == ENV) // WORKED
		return (exec_env(cmd[1] ,envp));
	else if (type == EXIT) // WORKED
		exec_exit(cmd, mish);
	else if (type == HISTORY) // WORKED
		return (exec_history(cmd));
	return (0);
}
