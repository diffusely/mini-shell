/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:16:42 by vmakarya          #+#    #+#             */
/*   Updated: 2025/10/11 19:42:20 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "lexer.h"
#include "shell.h"
#include "free.h"

volatile sig_atomic_t	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	*mish;

	(void)argv;
	if (argc != 1)
		ft_err("Error: no arguments allowed\n");
	mish = init_shell(envp);
	shell_loop(mish);
	free_all(mish);
	return (0);
}
