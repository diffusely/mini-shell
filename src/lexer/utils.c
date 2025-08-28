/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 01:26:47 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/29 01:45:34 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	init_sub_val(t_token **start, t_token **after, int *depth, bool *v)
{
	*start = NULL;
	*after = NULL;
	*depth = 0;
	*v = true;
}
