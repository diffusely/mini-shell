/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 22:50:19 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/22 15:55:42 by vmakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_shell	*init_shell(char **envp)
{
	t_shell	*mish;

	mish = ft_calloc(1, sizeof(t_shell));
	if (!mish)
		error_handle("Bad alloc *mish*!\n", 1);
	mish->status = 0;
	mish->list_env = init_env(envp);
	mish->env = init_env_matrix(mish->list_env);
	mish->tree = NULL;
	mish->fd_in = dup(STDIN_FILENO);
	mish->fd_out = dup(STDOUT_FILENO);
	mish->free = mish;
	return (mish);
}

void	shell_loop(t_shell *mish)
{
	while (1)
	{
		mish->input = readline("minishell$ ");
		if (!mish->input)
		{
			printf("exit\n");
			break ;
		}
		if (!*mish->input)
		{
			if (is_space_or_newline(mish->input))
			{
				free(mish->input);
				continue ;
			}
		}
		mish->token = lexer(mish->input);
		mish->free_token = mish->token;
		add_history(mish->input);
		add_history_input(mish);
		if (!syntax_check(mish->token))
		{
			free_mish(mish);
			continue ;
		}
		mish->tree = create_tree(&mish->token);
		mish->status = exec_ast(mish);
		free_mish(mish);
	}
}
