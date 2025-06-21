/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:41:41 by noavetis          #+#    #+#             */
/*   Updated: 2025/06/21 15:54:49 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include "ft_printf.h"
# include "free.h"
# include "message.h"

typedef enum e_token_type
{
	HEREDOC, // <<
	APPEND,  // >>
	WORD,    // echo hello
	PIP,     // |
	OUT,     // >
	IN,      // <
	END      // end
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

void		push_token(t_token	**tokens, t_token *temp);
void		free_tokens(t_token *tokens);
t_token		*lexer(const char *line);
void		print_tokens(t_token *lexer);

#endif