/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:45:33 by ernda-si          #+#    #+#             */
/*   Updated: 2025/06/23 11:35:16 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	wait_for_last(t_cmd *cmd_list, t_hell *shell)
// {
// 	int		status;
// 	t_cmd	*tmp;
// 	t_cmd	*last;

// 	tmp = cmd_list;
// 	last = cmd_list;
// 	while(last->next)
// 		last = last->next;
// 	status = 0;
// 	while (tmp)
// 	{
// 		if (tmp->pid > 0)
// 		{
// 			if (tmp == last)
// 			{
// 				waitpid(tmp->pid, &status, 0);
// 				if (WIFEXITED(status))
// 					shell->status = WEXITSTATUS(status);
// 				else if (WIFSIGNALED(status))
// 					shell->status = 128 + WTERMSIG(status);
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// }

static void	wait_for_all(t_cmd *cmd_list, t_hell *shell)
{
	int		status;
	t_cmd	*tmp;

	tmp = cmd_list;
	status = 0;
	while (tmp)
	{
		if (tmp->pid > 0)
		{
			waitpid(tmp->pid, &status, 0);
			if (WIFEXITED(status))
				shell->status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->status = 128 + WTERMSIG(status);
		}
		tmp = tmp->next;
	}
}

static void	prepare_heredocs(t_cmd *cmd_list)
{
	t_cmd			*cmd;
	t_redirection	*redir;

	cmd = cmd_list;
	while (cmd)
	{
		redir = cmd->redir_in;
		while (redir)
		{
			if (redir->type == LIM)
				do_heredoc(redir);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

static int redir_built_ins(t_cmd *cmd, t_hell *shell)
{
	int		orig_stdin;
	int		orig_stdout;

	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	if (orig_stdin == -1 || orig_stdout == -1)
		return (1);
	handle_redirections(cmd);
	shell->status = execute_builtin(cmd, shell);
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
	close(orig_stdin);
	close(orig_stdout);
	return (0);
}

void	execute_pipeline(t_hell *shell)
{
	t_cmd	*cmd;
	int		prev_pipe;
	int		pipes[2];

	cmd = shell->cmd;
	prev_pipe = -1;
	prepare_heredocs(shell->cmd);
	while (cmd)
	{
		if (!cmd->is_piped && cmd->is_builtin)
		{
			redir_built_ins(cmd, shell);
			return ;
		}
		if (cmd->is_piped && pipe(pipes) == -1)
		{
			perror("pipe");
			mini_cleaner(NULL, shell, EXIT_FAILURE);
		}
		stop_parent_signals();
		cmd->pid = fork();
		if (cmd->pid == -1)
		{
			perror("fork");
			mini_cleaner(NULL, shell, EXIT_FAILURE);
		}
		else if (cmd->pid == 0)
		{
			// do_heredoc(cmd);
			// shell->cmd = cmd;
			execute_child(cmd, prev_pipe, pipes, shell);
		}
		if (prev_pipe != -1)
			close(prev_pipe);
		if (cmd->is_piped)
		{
			close(pipes[1]);
			prev_pipe = pipes[0];
		}
		else
			prev_pipe = -1;
		cmd = cmd->next;
	}
	wait_for_all(shell->cmd, shell);
	signal_handler(shell, 'P');
}
