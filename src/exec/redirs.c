/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:18:28 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/17 13:21:11 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	shell_heredoc(char *limiter)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	signal_handler(get_hell(NULL), 'H');
	input_heredoc(pipefd[1], limiter);
	close(pipefd[1]);
	return (pipefd[0]);
}

static void	do_heredoc(t_redirection *redir)
{
	int	fd;

	signal_handler(get_hell(NULL), 'H');
	fd = shell_heredoc(redir->limiter);
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	open_infile(t_redirection *redir)
{
	redir->fd = open(redir->filename, O_RDONLY);
	if (redir->fd == -1)
	{
		perror(redir->filename);
		exit(EXIT_FAILURE);
	}
	dup2(redir->fd, STDIN_FILENO);
	close(redir->fd);
}

static void	open_outfile(t_redirection *redir, int append)
{
	int	flags;

	if (append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	redir->fd = open(redir->filename, flags, 0644);
	if (redir->fd == -1)
	{
		perror(redir->filename);
		exit(EXIT_FAILURE);
	}
	dup2(redir->fd, STDOUT_FILENO);
	close(redir->fd);
}

void	handle_redirections(t_cmd *cmd)
{
	t_redirection	*in;
	t_redirection	*out;

	in = cmd->redir_in;
	out = cmd->redir_out;
	while (in)
	{
		if (in->type == INFILE)
			open_infile(in);
		else if (in->type == LIM)
			do_heredoc(in);
		in = in->next;
	}
	while (out)
	{
		if (out->type == OUTFILE)
			open_outfile(out, 0);
		else if (out->type == OUTFILE_APPEND)
			open_outfile(out, 1);
		out = out->next;
	}
}
