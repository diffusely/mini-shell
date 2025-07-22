/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:36:19 by noavetis          #+#    #+#             */
/*   Updated: 2025/07/22 22:46:42 by vmakarya         ###   ########.fr       */
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

	token = NULL;
	free_token = NULL;
	input = NULL;
	tree = NULL;
	(void)argc;
	(void)argv;
	(void)envp;
	printf("porcnakan\n");
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		input = readline("minishell$ ");

		if (!input)
		{
			write(1, "exit\n", 5);
			break;
		}

		if (!exec_pwd(input))
		{
			free_all(tree, input, free_token);
			break ;
		}
 
		exec_cd(input);

		if (*input && is_history(input))
			print_history(tree, input, token);
		add_history_input(tree, input, token);
		
		token = lexer(input);
		print_tokens(token);
		free_token = token;
		tree = parse_expr(&token);
		
		print_ast(tree, 0);
		
		if (!ft_strcmp(input, "e"))
		{
			free_all(tree, input, free_token);
			break;
		}   
		free_all(tree, input, free_token);
	}
	return (0);
}
