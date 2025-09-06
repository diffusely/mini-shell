/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 21:16:26 by noavetis          #+#    #+#             */
/*   Updated: 2025/09/07 01:47:30 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	open_fd(void)
{
	int	fd;

	fd = open("history.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		perror("minishell: history");
	return (fd);
}

bool	valid_cmd(char *input)
{
	if (!input)
		return (true);
	return (false);
}

void	print_history(void)
{
	int		fd;
	int		count;
	char	*str;

	count = 1;
	fd = open_fd();
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

	fd = open("history.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return ;
	write(fd, mish->input, ft_strlen(mish->input));
	write(fd, "\n", 1);
	close(fd);
}
