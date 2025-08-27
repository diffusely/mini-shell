/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 21:16:26 by noavetis          #+#    #+#             */
/*   Updated: 2025/08/27 20:18:28 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	open_fd(t_shell *mish)
{
	int	fd;

	fd = open("history.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		free_all(mish);
		error_handle("", 0);
	}
	return (fd);
}

bool	is_history(char *input)
{
	if (!input)
		return (false);
	while (*input && ft_isspace(*input))
		input++;
	if (!ft_strncmp(input, "history", 7))
		input += 7;
	while (*input && ft_isspace(*input))
		input++;
	if (*input)
		return (false);
	return (true);
}

void	print_history(t_shell *mish)
{
	int		fd;
	int		count;
	char	*str;

	count = 1;
	fd = open_fd(mish);
	str = get_next_line(fd);
	while (str)
	{
		ft_putnbr_fd(count++, 1);
		printf(" %s", str);
		free(str);
		str = get_next_line(fd);
	}
	get_next_line(-1);
	close(fd);
}

void	add_history_input(t_shell *mish)
{
	int		fd;

	fd = open_fd(mish);
	write(fd, mish->input, ft_strlen(mish->input));
	write(fd, "\n", 1);
	close(fd);
}
