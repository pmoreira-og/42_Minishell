/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:11:56 by ernda-si          #+#    #+#             */
/*   Updated: 2025/05/21 12:37:29 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printascii(void)
{
	printf(
		" ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██▓█████  ██     ██    \n"
		"▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▓█   ▀ ▓██    ▓██    \n"
		"▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██▒███   ▒██    ▒██    \n"
		"▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██▒▓█  ▄ ▒██    ▒██    \n"
		"▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██░▒████▒░█████▒░█████▒\n"
		"░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░░░ ▒░ ░░ ▒▓  ░░ ▒▓  ░\n"
		"░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░  ░ ░  ░░ ░▒  ░░ ░▒  ░\n"
		"░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░    ░     ░░     ░░   \n"
		"       ░    ░           ░  ░        ░   ░  ░     ░  ░   ░  ░   ░  ░\n"
		"                                                                   \n"
		);
}

int	get_history_fd(t_hell *cmd)
{
	cmd->hist_fd = open(HIST_FILE, O_RDWR | O_APPEND | O_CREAT , 0766);
	if (cmd->hist_fd == -1)
		return (printf("DEU RUIM"), 1);
	return (0);
}

void load_history(t_hell *cmd)
{
	char		*temp;
	char	temp2[1024];
	int			size;

	if (cmd->hist_fd == -1)
		return ;
	ft_bzero(&temp2, 1024);
	while (1)
	{
		temp = get_next_line(cmd->hist_fd);
		if (!temp)
			break ;
		size = ft_strlen(temp);
		ft_strlcpy(temp2, temp, size);
		add_history(temp2);
		free(temp);
	}
}

void save_history(char *input, t_hell *cmd)
{
	if (cmd->hist_fd == -1 || !input || !ft_strcmp(input, ""))
		return;
	ft_putendl_fd(input, cmd->hist_fd);
	add_history(input);
}
