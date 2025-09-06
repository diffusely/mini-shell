/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:16:42 by vmakarya          #+#    #+#             */
/*   Updated: 2025/09/07 01:18:12 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "lexer.h"
#include "shell.h"
#include "free.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell *mish;

	(void)argv;
	if (argc != 1)
		 ft_err("Error: no arguments allowed\n");
	mish = init_shell(envp);
	
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
		
		mish->token = lexer(mish->input);
		mish->free_token = mish->token;
		//print_tokens(mish->token);
		add_history(mish->input);
		add_history_input(mish);
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
