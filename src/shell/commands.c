/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:19:55 by vmakarya          #+#    #+#             */
/*   Updated: 2025/08/14 20:14:09 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int find_word_place(char *word)
{
	int i;

	i = 0;
	while (word && word[i] && word[i] != '=')
		i++;
	return (i);
}

bool remove_list(const char *input, t_list **envp_list)
{
	t_list *curr = *envp_list;
	t_list *prev = NULL;

	while (curr)
	{
		if (curr->content && ft_strchr(curr->content, '=')) 
		{
			int place = find_word_place(curr->content);
			if (ft_strncmp(curr->content, input, place) == 0)
			{
				if (prev == NULL)
				{
					printf( "mtav ste\n");
					*envp_list = curr->next;
				}
				else
					prev->next = curr->next;
				free(curr->content);
				free(curr);
				return (true);
			}
		}
		prev = curr;
		curr = curr->next;
	}
	return (false);
}

void check_unset(char *input, t_list **env_list)
{
	while (*input && ft_isspace(*input))
		input++;
	if (ft_strncmp(input, "unset", 5) == 0)
		input += 5;
	else
		return ;
	while (*input && ft_isspace(*input))
		input++;
	remove_list(input, env_list);
	return ;
}

void init_env(char **envp, t_list **list_env)
{
	int	i;
	char *copy;

	i = 0;
	if (*list_env == NULL)
	{
		while (envp[++i])
		{
			copy = malloc(ft_strlen(envp[i]) + 1);
			if (!copy)
				return ;
			ft_strcpy(copy, envp[i]);
			t_list *node = ft_lstnew(copy);
			if (!node)
			{
				free(copy);
				return ;
			}
			ft_lstadd_back(list_env, node);
		}
	}
}

bool builtins(t_list **list_env, char *input, t_ast	*tree, t_token *free_token)
{
	while(1)
	{
		exec_env(input, list_env);
		check_unset(input, list_env);

		if (!ft_strcmp(input, "e"))
			return (free_all(tree, input, free_token), false);
		else if (!exec_pwd(input))
			return (free_all(tree, input, free_token), false);
		else if (!exec_cd(input, list_env))
			return (free_all(tree, input, free_token), false);
		else
			return (true);
	}
	if (chdir(input) == 0)
		return (true);
	return (true);
}
