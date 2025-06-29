/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:19:13 by noavetis          #+#    #+#             */
/*   Updated: 2025/06/30 00:14:43 by vmakarya         ###   ########.fr       */
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
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);

		while ((input = readline("minishell$ ")))
		{
			if (!input)
			{
				write(1, "exit\n", 5);
				break;
			}
			if (*input)
				add_history(input);
			free(input);
		}
		token = lexer(input);
		print_tokens(token);
		tree = parse_pipe(&token);
		print_ast(tree, 0);

		if (input[0] == 'e')
		{
			free_tree(tree);
			free(input);
			break;
		}

		free_tree(tree);
		free(input);
	}
	
	return (0);
}
