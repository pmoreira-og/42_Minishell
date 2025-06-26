/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:45:33 by ernda-si          #+#    #+#             */
/*   Updated: 2025/06/26 11:37:04 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Get pid exit status and save it on Main struct status.
void	get_status(int pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		get_hell(NULL)->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		get_hell(NULL)->status = 128 + WTERMSIG(status);
}

static int	redir_built_ins(t_cmd *cmd, t_hell *shell)
{
	shell->status = execute_builtin(cmd, shell);
	return (0);
}

// static void exec_checkers()
// {

// }

void	execute_pipeline(t_hell *shell)
{
	t_cmd	*cmd;
	int		prev_pipe;
	int		pipes[2];

	cmd = shell->cmd;
	prev_pipe = -1;
	if (prepare_heredocs(shell->cmd) && shell->status == 130)
		return ;
	while (cmd)
	{
		if (cmd->is_builtin && !cmd->redirs && !cmd->is_piped && !cmd->prev)
			return ((void) redir_built_ins(cmd, shell));
		if (cmd->is_piped && pipe(pipes) == -1)
			(perror("pipe"), mini_cleaner(NULL, shell, EXIT_FAILURE));
		stop_parent_signals();
		cmd->pid = fork();
		if (cmd->pid == -1)
			(perror("fork"), mini_cleaner(NULL, shell, EXIT_FAILURE));
		else if (cmd->pid == 0)
			execute_child(cmd, prev_pipe, &pipes[0], shell);
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
	(wait_for_all(shell->cmd, shell), signal_handler(shell, 'P'));
}
