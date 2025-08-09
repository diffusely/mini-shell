/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:54:54 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/09 15:02:08 by vmakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
					*envp_list = curr->next;
				else
					prev->next = curr->next;
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
	find_list(input, env_list);
	return ;
}

void exec_home(const char *input)
{
	while (*input && ft_isspace(*input))
		input++;
	if (ft_strncmp(input, "cd", 2) == 0)
		input += 2;
	else
		return ;
	while (*input && ft_isspace(*input))
		input++;
	if (!(*input))
		if(chdir(getenv("HOME")) == 0)
				return ;
}

bool	exec_cd(const char *input, t_list *envp_list)
{
	while (*input && ft_isspace(*input))
		input++;
	if (ft_strncmp(input, "cd", 2) == 0)
		input += 2;
	else
		return (false);
	while (*input && ft_isspace(*input))
		input++;
	if (!(*input))
	  {
		if(!find_list("HOME", &envp_list) && chdir(getenv("HOME")) == 0)
				return (true);
		else 
			return (printf("%s\n", "chka Home dir"), false);
	  }
	if (!find_list(input, &envp_list) && chdir(input) == 0)
		return (true);
	printf("cd: no such file or directory: %s\n", input);
	return (false);
}

int	exec_pwd(const char *input)
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
}

static void print_env(t_list *env)
{
	while (env)
	{
		if(env->content)
			printf("%s\n", (char *)env->content);
		env = env->next;
	}
}

void exec_env(char *input, t_list **list_env)
{
	while (*input && ft_isspace(*input))
		input++;
	if (ft_strncmp(input, "env", 3) != 0)
		return ;
	input += 3;
	while (*input && ft_isspace(*input))
		input++;
	if (*input != '\0')
	{
		printf("env: too many arguments\n");
		return ;
	}
	print_env(*list_env);
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
