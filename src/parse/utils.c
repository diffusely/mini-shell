/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:59:22 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/13 20:00:12 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	helper_ast(t_ast **node, t_token **tokens)
{
	t_token	*head;
	int		count;

	if (*tokens)
		*tokens = (*tokens)->next;
	count = 0;
	head = *tokens;
	while (head && head->type == WORD)
	{
		++count;
		head = head->next;
	}
	realoc_node(node, *tokens, count);
	while (*tokens && (*tokens)->type == WORD)
		*tokens = (*tokens)->next;
}
