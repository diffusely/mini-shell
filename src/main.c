/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:19:13 by noavetis          #+#    #+#             */
/*   Updated: 2025/07/05 17:54:11 by vmakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "lexer.h"
#include "shell.h"

int	main(int argc, char **argv, char **envp)
{
	t_token	*token;
	t_token *free_token;
	char	*input;
	t_ast	*tree;
	int		fd;
	char	*history;
	int		history_size;

	history_size = 0;
	history = NULL;
	fd = 0;
	(void)argc;
	(void)argv;
	(void)envp;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	if(open_fd(fd) == -1)
		return (0);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			write(1, "exit\n", 5);
			close(fd);
			free(history);
			break;
		}
		if (*input)
			add_history(input);
		token = lexer(input);
		free_token = token;
		history_settings(fd, input, history, history_size);
		// {
		// 	free(history);
		// 	close(fd);
		// 	return (0);	
		// }
		print_tokens(token);
		tree = parse_expr(&token);
		print_ast(tree, 0);
		
		if (!ft_strcmp(input, "e"))
		{
			free_tree(tree);
			free_tokens(free_token);
			free(input);
			free(history);
			close(fd);
			break;
		}
		free_tree(tree);
		free_tokens(free_token);
		free(input);
	}
	return (0);
}
