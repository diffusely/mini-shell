/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:12:28 by noavetis          #+#    #+#             */
/*   Updated: 2025/07/18 17:59:20 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void sigint_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	open_fd()
{
	int	fd;

	fd = open("output.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		error_handle("", 0);
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

void	print_history()
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

void	add_history(const char *input)
{
	int		fd;

	fd = open_fd();
	write(fd, input, ft_strlen(input));
	write(fd, "\n", 1);
	close(fd);
}
