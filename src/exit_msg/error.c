/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:37:14 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/15 02:25:49 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "message.h"

void	error_print(const char *cmd, const char *msg, int flag)
{
	printf("%s: %s", cmd, msg);
	if (flag)
		perror(msg);
	exit(EXIT_FAILURE);
}

void	error_handle(char *msg, int flag)
{
	if (flag)
		ft_putstr_fd(msg, 2);
	else
		perror(msg);
	exit(EXIT_FAILURE);
}

void	ft_err(char *msg)
{
	ft_putstr_fd(msg, 2);
}

