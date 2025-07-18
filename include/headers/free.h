/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:22:02 by noavetis          #+#    #+#             */
/*   Updated: 2025/07/18 20:26:05 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "libft.h"
# include "lexer.h"
# include "ast.h"

void	free_split(char **str);
void	free_all(t_ast *tree, char *input, t_token *token);
void	free_tokens(t_token *tokens);
void	free_tree(t_ast *root);

#endif