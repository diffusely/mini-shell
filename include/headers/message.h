/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:34:24 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/15 02:11:19 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_H
# define MESSAGE_H

# include "libft.h"

void	error_print(const char *cmd, const char *msg, int flag);
void	error_handle(char *msg, int flag);
void	ft_err(char *msg);
#endif