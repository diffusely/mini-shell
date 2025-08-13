/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:36:19 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/13 18:04:54 by vmakarya         ###   ########.fr       */
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
	
	while (1)
	{
		input = readline("minishell$ ");
		
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		init_env(envp, &list_env);
		// if (*input && is_history(input))
		// print_history(tree, input, token);
		// add_history_input(tree, input, token);
		
		token = lexer(input);
		// print_tokens(token);
		free_token = token;
		tree = parse_expr(&token);
		// print_ast(tree, 0);
		
		if(!builtins(&list_env, input, tree, free_token))
			break ;
	}
	return (0);
}
