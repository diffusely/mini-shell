/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:41:41 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/06 21:34:52 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include "message.h"
# include "shell.h"

typedef enum e_token_type
{
	HEREDOC,
	APPEND,
	WORD,
	PIP,
	AND,
	OR,
	LPAR,
	RPAR,
	OUT,
	IN,
	END
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

// Lexer functions
void		push_token(t_token	**tokens, t_token *temp);
t_token		*create_token(t_token_type type, char *value);
t_token		*lexer(const char *line);
bool		syntax_validation(t_token *input);
bool		syntax_help(t_token *cur);

// Print
void		print_tokens(t_token *lexer);

// Utils
void		init_sub_val(t_token **st, t_token **a, int *d, bool *v);
bool		syntax_check(t_token *input);
bool		is_and(const char *line, int i);
void		check_type(t_token *tok);

#endif