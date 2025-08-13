/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:54:54 by noavetis          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/22 23:38:02 by noavetis         ###   ########.fr       */
=======
/*   Updated: 2025/08/13 18:10:50 by vmakarya         ###   ########.fr       */
>>>>>>> built-in
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

<<<<<<< HEAD
bool	exec_cd(const char *input)
=======
static int find_word_place(char *word)
{
	int i;

	i = 0;
	while (word[i] && word[i] != '=')
		i++;
	return (i);
}

bool find_list(const char *input, t_list **envp_list)
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
>>>>>>> built-in
{
	while (*input && ft_isspace(*input))
		input++;
	if (ft_strncmp(input, "unset", 5) == 0)
		input += 5;
	else
		return ;
	while (*input && ft_isspace(*input))
		input++;
	find_list(input, env_list);
	return ;
}

// void exec_home(const char *input)
// {
// 	while (*input && ft_isspace(*input))
// 		input++;
// 	if (ft_strncmp(input, "cd", 2) == 0)
// 		input += 2;
// 	else
// 		return ;
// 	while (*input && ft_isspace(*input))
// 		input++;
// 	if (!(*input))
// 		if(chdir(getenv("HOME")) == 0)
// 				return ;
// }

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
		{
			free_all(tree, input, free_token);
			return (false);
		}
		else if (!exec_pwd(input))
		{
			free_all(tree, input, free_token);
			return (false);
		}
		else if (!exec_cd(input, list_env))
		{
			free_all(tree, input, free_token);
			return (false);
		}
		else
			return (true);
	}
<<<<<<< HEAD
	if (chdir(input) == 0)
		return (true);
	printf("cd: no such file or directory: %s\n", input);
	return (false);
}

bool	exec_pwd(const char *input)
{
	char	*pwd;

	if (!input)
		return (false);
	while (*input && ft_isspace(*input))
		input++;
	if (!ft_strncmp(input, "pwd", 3))
		input += 2;
	else
		return (true);
	while (*input && ft_isspace(*input))
		input++;
	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
		return (true);
	}
	return (false);
=======
>>>>>>> built-in
}
