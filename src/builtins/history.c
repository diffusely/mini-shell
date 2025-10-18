/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <noavetis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 00:23:21 by noavetis          #+#    #+#             */
/*   Updated: 2025/10/13 20:51:48 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

int	exec_history(t_shell *mish, char **cmd)
{
	if (!valid_cmd(cmd[1]))
	{
		ft_err("minishell: history: ");
		ft_err(cmd[1]);
		ft_err(": numeric argument required\n");
		return (1);
	}
	return (print_history(mish));
}

void	exec_exit(char **cmd, t_shell *mish)
{
	int	num;

	ft_putstr_fd("exit\n", 1);
	if (!valid_cmd(cmd[1]))
	{
		if (!valid_cmd(cmd[2]))
		{
			ft_err("minishell: exit: too many arguments\n");
			free_all(mish);
			exit(1);
		}
		if (check_exit_num(cmd[1]))
		{
			num = ft_atoi(cmd[1]);
			free_all(mish);
			exit(num);
		}
		ft_err("minishell: exit: ");
		ft_err(cmd[1]);
		ft_err(": numeric argument required\n");
		free_all(mish);
		exit(2);
	}
	free_all(mish);
	exit(0);
}

static int	open_fd(t_shell *mish, bool flag)
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

int	print_history(t_shell *mish)
{
	int		fd;
	int		count;
	char	*str;

	count = 1;
	fd = open_fd(mish, true);
	if (fd == -1)
		return (1);
	str = get_next_line(fd);
	while (str)
	{
		printf("%d %s", count++, str);
		free(str);
		str = get_next_line(fd);
	}
	get_next_line(-1);
	return (close(fd), 0);
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
