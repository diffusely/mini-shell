/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:16:42 by vmakarya          #+#    #+#             */
/*   Updated: 2025/08/15 19:47:37 by vmakarya         ###   ########.fr       */
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
		// print_tokens(token);
		mish->free_token = mish->token;
		mish->tree = create_tree(&mish->token);
		// print_ast(tree, 0);
		validate_ast(mish->tree);
		//print_ast(mish->tree, 0);
		
		if(!check_builtins(mish->input, &mish->list_env))
		{
			free_all(mish->tree, mish->input, mish->free_token);
			break ;
		}
	}
	return (0);
}
