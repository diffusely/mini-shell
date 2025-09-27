/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 22:50:19 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/28 00:31:43 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_shell	*init_shell(char **envp)
{
	t_shell	*mish;

	mish = ft_calloc(1, sizeof(t_shell));
	if (!mish)
		error_handle("Bad alloc *mish*!\n", 1);
	mish->status = 0;
	mish->list_env = init_env(envp);
	mish->env = init_env_matrix(mish->list_env);
	mish->tree = NULL;
	mish->fd_in = dup(STDIN_FILENO);
	mish->fd_out = dup(STDOUT_FILENO);
	mish->free = mish;
	return (mish);
}

static void	expand_wildcard(t_token **temp, bool quated)
{
	t_token	*tmp;
	char	**match;

	tmp = *temp;
	if (tmp->prev && tmp->prev->type != HEREDOC
		&& tmp->type == WORD && tmp->value 
		&& !quated && ft_strchr(tmp->value, '*'))
	{
		match = wildcard_expand(tmp->value);
		if (match)
		{
			t_token_type type = tmp->type;
			free(tmp->value);
			tmp->value = ft_strdup(match[0]);
			t_token *cur = tmp;
			for (int i = 1; match[i]; i++)
			{
				t_token *new_tok = ft_calloc(1, sizeof(t_token));
				new_tok->value = ft_strdup(match[i]);
				new_tok->type = type;
				new_tok->next = cur->next;
				cur->next = new_tok;
				cur = new_tok;
			}
			free_split(match);
			tmp = cur->next;
		}
	}
}

static void	expand_and_exec(t_shell *mish)
{
	t_token	*tmp;
	bool	quated;

	quated = false;
	tmp =  mish->token;
	while (tmp)
	{
		quated = false;
		if (tmp->value && (ft_strchr(tmp->value, '\'') || ft_strchr(tmp->value, '"')))
			quated = true;
		if (tmp->type != HEREDOC)
			tmp->value = expand(tmp->value, mish);
		if (tmp->value && tmp->value[0] == '\0' && !quated)
		{
			free(tmp->value);
			tmp->value = NULL;
		}
		expand_wildcard(&tmp, quated);
		tmp = tmp->next;
	}
	mish->tree = create_tree(&mish->token);
	mish->status = exec_ast(mish);
	free_mish(mish);
}

static bool	token_and_syntax(t_shell *mish)
{
	mish->token = lexer(mish->input);
	mish->free_token = mish->token;
	add_history(mish->input);
	add_history_input(mish);
	if (!syntax_check(mish->token))
		return (free_mish(mish), false);
	return (true);
}

void	shell_loop(t_shell *mish)
{
	while (1)
	{
		mish->input = readline("minishell$ ");
		if (!mish->input)
		{
			printf("exit\n");
			break ;
		}
		if (!*mish->input)
		{
			if (is_space_or_newline(mish->input))
			{
				free(mish->input);
				continue ;
			}
		}
		if (!token_and_syntax(mish))
		{
			mish->status = 2;
			continue ;
		}
		expand_and_exec(mish);
	}
}
