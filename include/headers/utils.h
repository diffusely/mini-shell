/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 22:31:16 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/24 01:58:05 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "lexer.h"

typedef enum e_token_type	t_token_type;

// Enum type
t_token_type	token_type(char first, char second);
int				is_built(char **cmd);
char			*token_value(t_token_type type);

// Quoted type
bool			is_space_or_newline(char *input);
bool			is_quoted(char c);
bool			check_quoted(const char *input);

// Token type
bool			is_redirect(t_token_type type);
bool			is_operator(t_token_type type);
bool			is_subshell(t_token_type type);
bool			is_and(const char *line, int i);
bool			valid_cmd(char *input);

#endif