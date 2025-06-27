/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:19:13 by noavetis          #+#    #+#             */
/*   Updated: 2025/06/27 15:08:38 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ft_printf.h"
#include "lexer.h"
#include "shell.h"

int	main(int argc, char **argv, char **envp)
{
	t_token	*token;
	char	*input;
	t_ast	*tree;

	(void)argc;
	(void)argv;
	(void)envp;

	while (1)
	{
		input = readline("minishell$");
		token = lexer(input);
		print_tokens(token);
	
		
		if (input[0] == 'e')
			break;

		tree = parse_pipe(token);
		print_ast(tree, 0);
		
		free_tree(tree);
		free_tokens(token);
	}

	//print_ast(tree, 0);
	return (0);
}
