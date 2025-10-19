/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 22:50:19 by noavetis          #+#    #+#             */
/*   Updated: 2025/10/18 23:54:34 by noavetis         ###   ########.fr       */
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
	mish->l_count = 1;
	mish->free = mish;
	return (mish);
}

static int	expand_wildcard(t_token *tmp, bool quated)
{
	char			**match;
	t_token			*cur;

	if (tmp->prev && tmp->prev->type != HEREDOC
		&& tmp->type == WORD && tmp->value
		&& !quated && ft_strchr(tmp->value, '*'))
	{
		match = wildcard_expand(tmp->value);
		if (match)
		{
			cur = tmp;
			create_wildcard_tok(tmp, cur, match);
			tmp = cur->next;
			return (free_split(match), 1);
		}
	}
	return (0);
}

static void	expand_and_exec(t_shell *mish)
{
	t_token	*tmp;
	bool	quated;

	quated = false;
	tmp = mish->token;
	while (tmp)
	{
		quated = false;
		if (tmp->value && (ft_strchr(tmp->value, '\'')
				|| ft_strchr(tmp->value, '"')))
			quated = true;
		if (tmp->prev && tmp->prev->type == HEREDOC)
		{
		}
		else
			tmp->value = expand(tmp->value, mish);
		if (tmp->value && tmp->value[0] == '\0' && !quated)
		{
			free(tmp->value);
			tmp->value = NULL;
		}
		if (expand_wildcard(tmp, quated))
			continue ;
		tmp = tmp->next;
	}
	mish->tree = create_tree(&mish->token);
	mish->status = exec_ast(mish);
	refresh_env_matrix(&mish);
}

static bool	token_and_syntax(t_shell *mish)
{
	t_token	*tmp;

	mish->token = lexer(mish->input);
	mish->free_token = mish->token;
	tmp = mish->token;
	add_history(mish->input);
	add_history_input(mish);
	while (tmp)
	{
		tmp->l_count = mish->l_count;
		tmp = tmp->next;
	}
	if (!syntax_check(mish->token))
		return (free_mish(mish), false);
	return (true);
}

void	shell_loop(t_shell *mish)
{
	while (1)
	{
		set_signals_prompt();
		mish->input = readline("minishell$ ");
		++mish->l_count;
		if (!mish->input)
		{
			printf("exit\n");
			break ;
		}
		if (g_signal == SIGINT)
		{
			mish->status = 130;
			g_signal = 0;
		}
		if (is_space_or_newline(mish->input))
			free(mish->input);
		else if (!token_and_syntax(mish))
			mish->status = 2;
		else
		{
			expand_and_exec(mish);
			free_mish(mish);
		}
	}
}
