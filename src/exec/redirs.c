/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:18:28 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/26 11:41:52 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	shell_heredoc(char *limiter, t_hell *data)
{
	int	pid;
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	stop_parent_signals();
	pid = fork();
	if (pid == 0)
	{
		if (data->hist_fd >= 0)
			close(data->hist_fd);
		signal_handler(get_hell(NULL), 'H');
		input_heredoc(pipefd[1], limiter);
		mini_cleaner(NULL, get_hell(NULL), 0);
	}
	else
		get_status(pid);
	signal_handler(get_hell(NULL), 'P');
	close(pipefd[1]);
	return (pipefd[0]);
}

void	do_heredoc(t_redirection *redir)
{
	redir->fd = shell_heredoc(redir->limiter, get_hell(NULL));
	if (redir->fd == -1)
		mini_cleaner(NULL, get_hell(NULL), EXIT_FAILURE);
}

static void	open_file(t_redirection *redir, t_type	type)
{
	int	flags;

	if (type == OUTFILE_APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else if (type == OUTFILE)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (type == INFILE)
		redir->fd = open(redir->filename, O_RDONLY);
	else
		redir->fd = open(redir->filename, flags, 0644);
	if (redir->fd == -1)
	{
		ft_printf_fd(2, "minishell: %s: ", redir->filename);
		perror(NULL);
		mini_cleaner(NULL, get_hell(NULL), EXIT_FAILURE);
	}
}

void	handle_redirections(t_cmd *cmd)
{
	t_redirection	*temp;

	temp = cmd->redirs;
	while (temp)
	{
		if (temp->type == OUTFILE)
			open_file(temp, OUTFILE);
		if (temp->type == OUTFILE_APPEND)
			open_file(temp, OUTFILE_APPEND);
		if (temp->type == INFILE)
			open_file(temp, INFILE);
		temp = temp->next;
	}
	update_fds(cmd);
}
