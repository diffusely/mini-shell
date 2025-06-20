/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:19:13 by noavetis          #+#    #+#             */
/*   Updated: 2025/06/20 21:59:11 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ast.h"
#include "lexer.h"
#include "shell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	t_token *token;
	
	while (1)
	{
		char	*input = readline("minishell$ ");

		token = lexer(input);

		
		print_tokens(token);

		t_ast *tree = parse_pipe(token);

		print_ast(tree, 0);

		if (input[0] == 'e')
		{
			get_next_line(-1);
			free(input);
			free_tokens(token);
			free_tree(tree);
			break ;
		}

		
		free(input);
		free_tokens(token);
		free_tree(tree);
	}
	
	

	
	return (0);
}
