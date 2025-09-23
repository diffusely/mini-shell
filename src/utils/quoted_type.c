/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 22:35:12 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/22 22:51:35 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	is_quoted(char c)
{
	return (c == '"' || c == '\'');
}

bool	is_space_or_newline(char *input)
{
	while (*input)
	{
		if (!ft_isspace(*input))
			return (false);
		input++;
	}
	return (true);
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
