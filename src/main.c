/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:19:13 by noavetis          #+#    #+#             */
/*   Updated: 2025/07/22 00:00:17 by noavetis         ###   ########.fr       */
=======
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:19:13 by noavetis          #+#    #+#             */
/*   Updated: 2025/07/22 15:48:52 by vmakarya         ###   ########.fr       */
>>>>>>> 9b8e807b3616ce9a4df3fdd1432f4c0a08c5ed05
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
			print_history();
		add_history(input);
		
		token = lexer(input);
		print_tokens(token);
		free_token = token;
		tree = parse_expr(&token);
		
<<<<<<< HEAD
		print_ast(tree, 0);
		
=======
		//print_ast(tree, 0);

>>>>>>> 9b8e807b3616ce9a4df3fdd1432f4c0a08c5ed05
		if (!ft_strcmp(input, "e"))
		{
			free_all(tree, input, free_token);
			break;
		}
		free_all(tree, input, free_token);
	}
	return (0);
}
