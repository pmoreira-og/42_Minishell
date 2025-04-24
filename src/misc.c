/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:11:56 by ernda-si          #+#    #+#             */
/*   Updated: 2025/04/24 16:57:56 by pmoreira         ###   ########.fr       */
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

int	get_history_fd(t_cmd *cmd)
{
	char	*temp;
	char	*path;
	
	temp = getcwd(NULL, 0);
	if (!temp)
		return (1);
	path = ft_strjoin(temp, HIST_FILE);
	if (!path)
		return (1);
	cmd->hist_fd = open(path, O_RDWR | O_CREAT , 0766);
	if (cmd->hist_fd == -1)
		return (printf("DEU RUIM"), 1);
	// free(temp);
	free(path);
	return (0);
}

void load_history(t_cmd *cmd)
{
	char	*temp;

	if (cmd->hist_fd == -1)
		return ;
	while (1)
	{
		temp = get_next_line(cmd->hist_fd);
		if (!temp)
			break ;
		add_history(temp);
		free(temp);
	}
}

void save_history(char *input, t_cmd *cmd)
{
	if (cmd->hist_fd == -1 || !input)
		return;
	write(cmd->hist_fd, input, ft_strlen(input));
	add_history(input);

}
