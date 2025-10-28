/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 01:19:10 by noavetis          #+#    #+#             */
/*   Updated: 2025/10/29 02:03:38 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*str_join_free(char *s1, char *s2)
{
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	res = ft_strjoin(s1, s2);
	return (free(s1), free(s2), res);
}

char	*str_join_char(char *s, char c)
{
	char	str[2];
	char	*tmp;

	str[0] = c;
	str[1] = '\0';
	tmp = ft_strjoin(s, str);
	return (free(s), tmp);
}

char	*expand_dollar(t_shell *mish, const char *s, int *i)
{
	char	*name;
	char	*value;
	int		start;

	(*i)++;
	value = NULL;
	if (mish && s[*i] == '?')
		return ((*i)++, ft_itoa(mish->status));
	start = *i;
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
		(*i)++;
	if (*i == start)
		return (ft_strdup("$"));
	name = ft_substr(s, start, *i - start);
	if (mish)
		value = find_list(name, &mish->list_env);
	free(name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static void	init_res(char *s, t_shell *mish, char **res, int *i)
{
	if (s[*i] == '"')
	{
		(*i)++;
		while (s[*i] && s[*i] != '"')
		{
			if (mish && s[*i] == '$')
				*res = str_join_free(*res, expand_dollar(mish, s, i));
			else
				*res = str_join_char(*res, s[(*i)++]);
		}
		if (s[*i] == '"')
			(*i)++;
	}
	else if (mish && s[*i] == '$')
		*res = str_join_free(*res, expand_dollar(mish, s, i));
	else
		*res = str_join_char(*res, s[(*i)++]);
}

char	*expand(char *s, t_shell *mish, bool flag)
{
	char	*res;
	int		start;
	int		i;

	i = 0;
	res = ft_strdup("");
	while (s[i])
	{
		if (s[i] == '\'')
		{
			start = ++i;
			while (s[i] && s[i] != '\'')
				++i;
			res = str_join_free(res, ft_substr(s, start, i - start));
			if (s[i] == '\'')
				i++;
		}
		else
			init_res(s, mish, &res, &i);
	}
	if (flag)
		free(s);
	return (res);
}
