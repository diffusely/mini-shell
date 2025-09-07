/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:16:42 by vmakarya          #+#    #+#             */
/*   Updated: 2025/09/08 00:43:56 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "lexer.h"
#include "shell.h"
#include "free.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell *mish;

	(void)argv;
	if (argc != 1)
		 ft_err("Error: no arguments allowed\n");
	mish = init_shell(envp);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	shell_loop(mish);
	free_all(mish);
	return (0);
}
