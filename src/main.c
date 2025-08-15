/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:16:42 by vmakarya          #+#    #+#             */
/*   Updated: 2025/08/15 03:10:48 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "lexer.h"
#include "shell.h"
#include "free.h"

int	main(int argc, char **argv, char **envp)
{
	t_token	*token;
	t_token *free_token;
	char	*input;
	t_ast	*tree;
	t_list	*list_env;

	list_env = NULL;
	token = NULL;
	free_token = NULL;
	input = NULL;
	tree = NULL;
	(void)argc;
	(void)argv;
	(void)envp;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	// input = readline("minishell$ ");
	// exec_home(input);
	init_env(envp, &list_env);
	while (1)
	{
		input = readline("minishell$ ");

		if (!*input)
		{
			if (is_space_or_newline(input))
			{
				free(input);
				continue ;
			}
		}
		
		// if (*input && is_history(input))
		// print_history(tree, input, token);
		// add_history_input(tree, input, token);
		
		token = lexer(input);
		//print_tokens(token);
		free_token = token;
		tree = create_tree(&token);
		validate_ast(tree);
		print_ast(tree, 0);
		
		if(!builtins(&list_env, input, tree, free_token))
			break ;
	}
	return (0);
}
