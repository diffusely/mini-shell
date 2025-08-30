/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:20:25 by vmakarya          #+#    #+#             */
/*   Updated: 2025/08/30 22:46:43 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char*	check(char *input, bool *new_line)
{
	if (!input)
		return (NULL);
	while (*input && ft_isspace(*input))
		++input;
	if (ft_strncmp(input, "echo", 4) == 0)
	{
		input += 4;
		while (*input && ft_isspace(*input))
			++input;
		if(ft_strncmp(input, "-n", 2) != 0)
			*new_line = true;
		return (input);
	}
	return (NULL);
}

char*	fix_new_line(bool new_line, char *input)
{
	int i;
	
	i = 0;
	if (new_line)
	{
		while (i <= 4 || ft_isspace(*input))
		{
			input++;
			i++;
		}
		i = 0;
		while(i <= 2 || ft_isspace(*input))
		{
			input++;
			i++;
		}
	} else {
		while (i <= 4 || ft_isspace(*input))
		{
			input++;
			i++;
		}
	}
	return (input);
}

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

void	check_dollar(char *input, t_list **list_env)
{
	char *cmd;

	input++;
	cmd = find_list(input, list_env);
	if (cmd)
		printf("%s", cmd);
}

bool	exec_echo(char *input, t_list **list_env)
{
	bool new_line;

	new_line = false;
	input = check(input, &new_line);
	while(*input)
	{
		if (*input == '"' && *(input + 1))
			++input;
		if (*input == '$')
		{
			check_dollar(input, list_env);
			if (new_line)
				printf("\n");
		}
		// else
		// 	printf("%c", *input);
		input++;
	}
	if (new_line)
		printf("\n");
	return (true);
}
