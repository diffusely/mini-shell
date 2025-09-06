/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 22:50:19 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/06 22:55:42 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_shell	*init_shell(char **envp)
{
	t_shell	*mish;

	mish = ft_calloc(1, sizeof(t_shell));
	if (!mish)
		error_handle("Bad alloc *mish*!\n", 1);
	mish->list_env = init_env(envp);
	mish->env = init_env_matrix(mish->list_env);
	mish->tree = NULL;
	mish->fd_in = dup(STDIN_FILENO);
	mish->fd_out = dup(STDOUT_FILENO);
	mish->free = mish;
	return (mish);
}
