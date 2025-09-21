/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 21:16:26 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/22 02:24:52 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	open_fd(t_shell *mish, bool flag)
{
	int			fd;
	char		*home;
	char		*path;
	const char	*fname;

	fname = "/history.txt";
	home = find_list("HOME", &mish->list_env);
	if (!home)
		home = ".";
	path = ft_calloc(1, ft_strlen(home) + ft_strlen(fname) + 1);
	if (!path)
		return (-1);
	ft_strcpy(path, home);
	ft_strcpy(path + ft_strlen(home), fname);
	fd = open(path, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1 && flag)
		perror("minishell: history");
	free(path);
	return (fd);
}

bool	valid_cmd(char *input)
{
	if (!input)
		return (true);
	return (false);
}

void	print_history(t_shell *mish)
{
	int		fd;
	int		count;
	char	*str;

	count = 1;
	fd = open_fd(mish, true);
	if (fd == -1)
		return ;
	str = get_next_line(fd);
	while (str)
	{
		printf("%d %s", count++, str);
		free(str);
		str = get_next_line(fd);
	}
	get_next_line(-1);
	close(fd);
}

void	add_history_input(t_shell *mish)
{
	int		fd;

	fd = open_fd(mish, false);
	if (fd == -1)
		return ;
	if (mish->input && mish->input[0] != '\0')
	{
		write(fd, mish->input, ft_strlen(mish->input));
		write(fd, "\n", 1);
	}
	close(fd);
}
