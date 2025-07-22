/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:22:02 by noavetis          #+#    #+#             */
/*   Updated: 2025/07/22 23:44:56 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "libft.h"
# include "lexer.h"
# include "ast.h"

typedef struct s_ast	t_ast;
typedef struct s_token	t_token;

void	free_split(char **str);
void	free_all(t_ast *tree, char *input, t_token *token);
void	free_tokens(t_token *tokens);
void	free_tree(t_ast *root);

#endif