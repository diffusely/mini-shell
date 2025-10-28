/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 21:27:14 by noavetis          #+#    #+#             */
/*   Updated: 2025/10/29 01:01:21 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

void	ft_err_msg(char *str, char *msg)
{
	ft_err(str);
	perror(msg);
}

int	f_w_p(char *word)
{
	int	i;

	i = 0;
	while (word && word[i] && word[i] != '=')
		++i;
	return (i);
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
		return (exec_echo(cmd));
	else if (type == UNSET)
		return (exec_unset(cmd, envp));
	else if (type == EXPORT)
		return (exec_export(cmd, envp));
	if (type == CD)
		return (exec_cd(cmd, envp, i));
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
	size_t	len;

	curr = *envp_list;
	while (curr)
	{
		if (curr->content && ft_strchr(curr->content, '='))
		{
			len = ft_strlen(input);
			if (!ft_strncmp(curr->content, input, len)
				&& ((char *)curr->content)[len]
				&& ((char *)curr->content)[len] == '=')
				return (((char *)curr->content) + len + 1);
		}
		curr = curr->next;
	}
	return (NULL);
}

bool	check_exit_num(char *input)
{
	int	i;

	if (!input)
		return (false);
	i = 0;
	if (input[0] == '+' || input[0] == '-')
		i++;
	while (input && ft_isdigit(input[i]))
		i++;
	if (input[i] == '\0')
		return (true);
	return (false);
}
