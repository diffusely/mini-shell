/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 21:27:14 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/22 01:43:49 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

void	ft_err_msg(char *str, char *msg)
{
	ft_err(str);
	ft_err(msg);
	ft_err("\n");
}

int	f_w_p(char *word)
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
	int		i;

	i = 0;
	tmp = NULL;
	type = is_built(cmd);
	if (type == ECHO)
		return (exec_echo(cmd, envp));
	else if (type == UNSET)
		return (exec_unset(mish, cmd, envp));
	else if (type == EXPORT)
		return (exec_export(cmd, envp));
	if (type == CD)
		return (exec_cd(&mish, cmd, envp, i));
	else if (type == PWD)
		return (exec_pwd(mish, tmp));
	else if (type == ENV)
		return (exec_env(cmd[1], envp));
	else if (type == EXIT)
		exec_exit(cmd, mish);
	else if (type == HISTORY)
		return (exec_history(mish, cmd));
	return (0);
}

char	*find_list(const char *input, t_list **envp_list)
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
				return (curr->content + place + 1);
		}
		curr = curr->next;
	}
	return (NULL);
}
