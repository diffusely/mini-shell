/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:37:14 by noavetis          #+#    #+#             */
/*   Updated: 2025/07/18 15:51:30 by noavetis         ###   ########.fr       */
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
