/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:45:33 by ernda-si          #+#    #+#             */
/*   Updated: 2025/06/17 13:24:28 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	execute_pipeline(t_hell *shell)
{
	t_cmd	*cmd;
	int		prev_pipe;
	int		pipes[2];

	cmd = shell->cmd;
	prev_pipe = -1;
	while (cmd)
	{
		if (!cmd->is_piped && cmd->is_builtin)
		{
			shell->status = execute_builtin(cmd, shell);
			return ;
		}
		if (cmd->is_piped && pipe(pipes) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		stop_parent_signals();
		cmd->pid = fork();
		if (cmd->pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (cmd->pid == 0)
		{
			shell->cmd = cmd;
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
