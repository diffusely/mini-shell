/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:34:24 by noavetis          #+#    #+#             */
/*   Updated: 2025/06/18 17:38:53 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_H
# define MESSAGE_H

# include "ft_printf.h"
# include "libft.h"

void	error_print(const char *cmd, const char *msg, int flag);
void	error_handle(char *msg, int flag);

#endif