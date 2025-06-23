/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:18:28 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/23 11:28:47 by pmoreira         ###   ########.fr       */
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
		wait(&data->status);
	if (WIFEXITED(data->status))
		data->status = WEXITSTATUS(data->status);
	signal_handler(get_hell(NULL), 'P');
	close(pipefd[1]);
	return (pipefd[0]);
}

void	do_heredoc(t_redirection *redir)
{
	
	redir->fd = shell_heredoc(redir->limiter, get_hell(NULL));
	if (redir->fd == -1)
		exit(EXIT_FAILURE);
	// dup2(fd, STDIN_FILENO);
	// close(fd);
}

// void	do_heredoc(t_cmd *cmd)
// {
// 	int				fd;
// 	t_redirection	*redir;

// 	redir = cmd->redir_in;
// 	fd = -1;
// 	while (redir)
// 	{
// 		if (redir->type == LIM)
// 		{
// 			if (fd != -1)
// 				close(fd);
// 			fd = shell_heredoc(redir->limiter);
// 			if (fd == -1)
// 				exit(EXIT_FAILURE);
// 		}
// 		redir = redir->next;
// 	}
// 	if (fd != -1)
// 		ft_dup(fd, STDIN_FILENO);
// }

static void	open_infile(t_redirection *redir)
{
	redir->fd = open(redir->filename, O_RDONLY);
	if (redir->fd == -1)
	{
		perror(redir->filename);
		exit(EXIT_FAILURE);
	}
	// dup2(redir->fd, STDIN_FILENO);
	// close(redir->fd);
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
	// dup2(redir->fd, STDOUT_FILENO);
	// close(redir->fd);
}

int	dup_redirs(t_cmd *cmd)
{
	t_redirection	*in;
	t_redirection	*out;

	in = cmd->redir_in;
	out = cmd->redir_out;
	while (in)
	{
		if (!in->next)
		{
			if (!ft_dup(in->fd, STDIN_FILENO))
				return (0);
		}
		in = in->next;
	}
	while (out)
	{
		if (!out->next)
		{
			if (!ft_dup(out->fd, STDOUT_FILENO))
				return (0);
		}
		out = out->next;
	}
	return (1);
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
		// else if (in->type == LIM)
		// 	do_heredoc(in);
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
	if (!cmd->is_piped && !dup_redirs(cmd))
		return (mini_cleaner(NULL, get_hell(NULL), 1));
	// else if (cmd->is_piped)
	// 	ft_dup(cmd->fd_out, STDOUT_FILENO);
}
