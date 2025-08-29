/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 01:26:47 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/29 18:11:09 by noavetis         ###   ########.fr       */
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

bool	syntax_check(t_token *input)
{
	t_token	*cur;

	cur = input;
	while (cur)
	{
		if (cur->type == LPAR)
			break ;
		if (cur->type == RPAR)
			return (check_type(cur), false);
		cur = cur->next;		
	}
	return (syntax_validation(input));
}
