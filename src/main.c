/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:19:13 by noavetis          #+#    #+#             */
/*   Updated: 2025/06/21 16:31:52 by noavetis         ###   ########.fr       */
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
	input = "a | a ";
	token = lexer(input);
	print_tokens(token);

	
	tree = parse_pipe(token);
	print_ast(tree, 0);
	
	free_tree(tree);
	free_tokens(token);
	//print_ast(tree, 0);
	return (0);
}
