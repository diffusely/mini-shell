/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 01:26:47 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/30 15:36:43 by noavetis         ###   ########.fr       */
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

bool	check_quoted(const char *input)
{
	bool	single_open;
	bool	double_open;
	int		i;

	i = 0;
	single_open = false;
	double_open = false;
	while (input[i])
	{
		if (input[i] == '\'' && !double_open)
			single_open = !single_open;
		else if (input[i] == '"' && !single_open)
			double_open = !double_open;
		i++;
	}
	return (single_open || double_open);
}

bool	is_and(const char *line, int i)
{
	if (line[i] && line[i + 1] && line[i] == '&' && line[i + 1] == '&')
		return (true);
	return (false);
}
