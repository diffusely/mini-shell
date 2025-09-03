/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:16:42 by vmakarya          #+#    #+#             */
/*   Updated: 2025/09/03 19:21:24 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "lexer.h"
#include "shell.h"
#include "free.h"

// void	init_minishell(t_shell **mish, int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	init_env(envp, &(*mish)->list_env);
// }

int	main(int argc, char **argv, char **envp)
{
	t_shell *mish;

	(void)argc;
	(void)argv;
	mish = ft_calloc(1, sizeof(t_shell));

	mish->list_env = init_env(envp);
	mish->env = init_env_matrix(mish->list_env);
	mish->tree = NULL;
	mish->fd_in = dup(STDIN_FILENO);
	mish->fd_out = dup(STDOUT_FILENO);

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		mish->input = readline("minishell$ ");
		if (!mish->input)
			break ;
		if (!*mish->input)
		{
			if (is_space_or_newline(mish->input))
			{
				free(mish->input);
				continue ;
			}
		}

		// if (*input && is_history(input))
		// print_history(tree, input, token);
		// add_history_input(tree, input, token);
		
		mish->token = lexer(mish->input);
		mish->free_token = mish->token;
		//print_tokens(mish->token);
		if (!syntax_check(mish->token))
		{
			free_mish(mish);
			continue ;
		}
		mish->tree = create_tree(&mish->token);
		
		//print_env_matrix(mish->env);
		//refresh_env_matrix(&mish);

		//print_ast(mish->tree, 0);
		mish->status = exec_ast(mish);



		
		//printf("exit\n");
		// if (!ft_strncmp(mish->input, "e", 1))
		// {
		// 	free_all(mish);
		// 	break ;
		// }

		free_mish(mish);
	}
	free_all(mish);
	return (0);
}
