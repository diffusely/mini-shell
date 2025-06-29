/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:19:13 by noavetis          #+#    #+#             */
/*   Updated: 2025/06/30 00:10:15 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ft_printf.h"
#include "lexer.h"
#include "shell.h"

int	main(int argc, char **argv, char **envp)
{
	t_token	*token;
	t_token	*free_token;
	char	*input;
	t_ast	*tree;

	(void)argc;
	(void)argv;
	(void)envp;

	while (1)
	{
		input = readline("minishell$");


		token = lexer(input);
		free_token = token;
		print_tokens(token);
	
		
		tree = parse_expr(&token);
		print_ast(tree, 0);

		if (input[0] == 'e')
		{
			free_tree(tree);
			free_tokens(free_token);
			free(input);
			break;
		}

		free_tree(tree);
		free_tokens(free_token);
		free(input);
	}

	//print_ast(tree, 0);
	
	return (0);
}
