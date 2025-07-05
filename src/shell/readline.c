/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:12:28 by noavetis          #+#    #+#             */
/*   Updated: 2025/07/05 17:52:48 by vmakarya         ###   ########.fr       */
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

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i = 0;

	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int open_fd(int fd)
{
		fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("open failed");
			return 1;
		}
	return (0); 
}

void history_settings(int fd, char *input, char *history, int history_size)
{
	size_t input_len = ft_strlen(input);
		char *new_history = malloc(history_size + input_len + 2);
		if (!new_history)
			return ;
		if (history)
		{
			ft_strncpy(new_history, history, history_size);
			free(history);
		}
		if (ft_strcmp(input, "history"))
			ft_strncpy(new_history + history_size, input, input_len);
		new_history[history_size + input_len] = '\n';
		new_history[history_size + input_len + 1] = '\0';
		history = new_history;
		history_size += input_len + 1;
		if (!ft_strcmp(input, "history"))
			printf("%s", history);
		else if (*input)
		{
			write(fd, input, input_len);
			write(fd, "\n", 1);
		}
}
