/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:11:56 by ernda-si          #+#    #+#             */
/*   Updated: 2025/07/14 15:46:30 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printascii(void)
{
	printf(RED
		"                                                                   \n"
		" ███▄ ▄███▓ ██▓ ███▄    █  ██▓          ██░ ██▓█████  ██     ██    \n"
		"▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒         ▓██░ ██▓█   ▀ ▓██    ▓██    \n"
		"▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒         ▒██▀▀██▒███   ▒██    ▒██    \n"
		"▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░         ░▓█ ░██▒▓█  ▄ ▒██    ▒██    \n"
		"▒██▒   ░██▒░██░▒██░   ▓██░░██░         ░▓█▒░██░▒████▒░█████▒░█████▒\n"
		"░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓            ▒ ░░▒░░░ ▒░ ░░ ▒▓  ░░ ▒▓  ░\n"
		"░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░          ▒ ░▒░  ░ ░  ░░ ░▒  ░░ ░▒  ░\n"
		"░      ░    ▒ ░   ░   ░ ░  ▒ ░          ░  ░░    ░     ░░     ░░   \n"
		"       ░    ░           ░  ░            ░  ░     ░  ░   ░  ░   ░  ░\n"
		"                                                                   \n"
		RESET);
}

int	get_history_fd(t_hell *cmd)
{
	cmd->hist_fd = open(HIST_FILE, O_RDWR | O_APPEND | O_CREAT, 0766);
	if (cmd->hist_fd == -1)
		return (1);
	return (0);
}

void	load_history(t_hell *cmd)
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

void	save_history(char *input, t_hell *cmd)
{
	if (!input || !ft_strcmp(input, ""))
		return ;
	if (cmd->hist_fd != -1)
		ft_putendl_fd(input, cmd->hist_fd);
	add_history(input);
}

char	*get_type(t_type type)
{
	if (type == CMD)
		return ("CMD");
	if (type == ARG)
		return ("ARG");
	if (type == PIPE)
		return ("PIPE");
	if (type == REDIR_IN)
		return ("REDIR_IN");
	if (type == REDIR_HERE_DOC)
		return ("REDIR_HERE_DOC");
	if (type == LIM)
		return ("LIM");
	if (type == REDIR_OUT)
		return ("REDIR_OUT");
	if (type == REDIR_OUT_APPEND)
		return ("REDIR_OUT_APPEND");
	if (type == BUILT_IN)
		return ("BUILT_IN");
	if (type == INFILE)
		return ("INFILE");
	if (type == OUTFILE)
		return ("OUTFILE");
	if (type == OUTFILE_APPEND)
		return ("OUTFILE_APPEND");
	return ("");
}
