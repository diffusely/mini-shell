/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:20:25 by vmakarya          #+#    #+#             */
/*   Updated: 2025/09/21 16:34:32 by vmakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char* find_list(const char* input, t_list **envp_list)
{
	t_list *curr;

	curr = *envp_list;
	while (curr)
	{
		if (curr->content && ft_strchr(curr->content, '=')) 
		{
			int place = find_word_place(curr->content);
			if (ft_strncmp(curr->content, input, place) == 0)
			{
				while (*(char *)curr->content != '=')
					curr->content++;
				curr->content++;
				return (curr->content);
			}
		}
		curr = curr->next;
	}
	return (NULL);
}

static void check_dollar(char *input, t_list **list_env, bool new_line)
{
    char *cmd;

    input++;
    cmd = find_list(input, list_env);

    if (cmd)
        printf("%s", cmd);
    else
        printf("");
    if (new_line)
        printf("\n");
}

char *remove_quotes(char *str)
{
    char *src = str;
    char *dst = str;

    if (!str)
        return NULL;

    while (*src)
    {
        if (*src != '\'' && *src != '"')
            *dst++ = *src;
        src++;
    }
    *dst = '\0';
    return (str);
}

static void print_arg(char *arg, t_list **envp)
{
    if (!arg)
        return;

    arg = remove_quotes(arg);

    if (arg[0] == '$')
        check_dollar(arg, envp, false);
    else
        printf("%s", arg);
}

bool	exec_echo(char **cmd, t_list **envp)
{
	bool	new_line;
	int		i;

	new_line = true;
	i = 1;
	if (cmd[i] && !strcmp(cmd[i], "-n"))
	{
		new_line = false;
		i++;
	}
	while (cmd[i])
	{
		print_arg(cmd[i], envp);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	return (true);
}
