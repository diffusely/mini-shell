/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:41:41 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/29 01:41:32 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include "message.h"
# include "shell.h"

typedef enum e_token_type
{
	HEREDOC, // <<
	APPEND,  // >>
	WORD,    // echo hello
	PIP,     // |
	AND,     // &&
	OR,      // ||
	LPAR,    // (
	RPAR,    // )
	OUT,     // >
	IN,      // <
	END      // end
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

// Print
void		print_tokens(t_token *lexer);

// Utils
void		init_sub_val(t_token **st, t_token **a, int *d, bool *v);


#endif