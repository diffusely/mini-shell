/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 21:53:20 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/28 13:37:08 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	match(const char *type, const char *name);

static int	help_match(const char *type, const char *name, int *i, int *j)
{
	if (type[*i] == '*')
	{
		if (type[*i + 1] == '\0')
			return (1);
		while (name[*j])
		{
			if (match(type + *i + 1, name + *j))
				return (1);
			(*j)++;
		}
		return (0);
	}
	else
	{
		if (type[*i] != name[*j])
			return (0);
		(*i)++;
		(*j)++;
	}
	return (-1);
}

static int	match(const char *type, const char *name)
{
	int	ret;
	int	i;
	int	j;

	if (!type || !name)
		return (0);
	i = 0;
	j = 0;
	while (type[i] && name[j])
	{
		ret = help_match(type, name, &i, &j);
		if (ret != -1)
			return (ret);
	}
	if (type[i] == '\0' && name[j] == '\0')
		return (1);
	if (type[i] == '*' && type[i + 1] == '\0')
		return (1);
	return (0);
}

void	create_wildcard_tok(t_token *tmp, t_token *cur, char **match)
{
	t_token_type	type;
	t_token			*new_tok;
	int				i;

	type = tmp->type;
	free(tmp->value);
	tmp->value = ft_strdup(match[0]);
	i = 1;
	while (match[i])
	{
		new_tok = ft_calloc(1, sizeof(t_token));
		new_tok->value = ft_strdup(match[i]);
		new_tok->type = type;
		new_tok->next = cur->next;
		cur->next = new_tok;
		cur = new_tok;
		i++;
	}
}

char	**wildcard_expand(const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;
	int				count;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	count = 0;
	matches = NULL;
	entry = readdir(dir);
	while (entry)
	{
		if (!(entry->d_name[0] == '.' && pattern[0] != '.')
			&& match(pattern, entry->d_name))
		{
			matches = ft_realloc(matches, count * sizeof(char *),
					sizeof(char *) * (count + 2));
			matches[count] = ft_strdup(entry->d_name);
			count++;
			matches[count] = NULL;
		}
		entry = readdir(dir);
	}
	return (closedir(dir), matches);
}
