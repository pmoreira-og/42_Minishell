/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:45:33 by ernda-si          #+#    #+#             */
/*   Updated: 2025/06/24 12:31:44 by pmoreira         ###   ########.fr       */
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



static int redir_built_ins(t_cmd *cmd, t_hell *shell)
{
	shell->status = execute_builtin(cmd, shell);
	return (0);
}

void	execute_pipeline(t_hell *shell)
{
	t_cmd	*cmd;
	int		prev_pipe;
	int		pipes[2];

	cmd = shell->cmd;
	prev_pipe = -1;
	//* SIGINT should stop all heredocs and go back to Minishell>
	prepare_heredocs(shell->cmd);
	while (cmd)
	{
		//* FORK on redirs and pipes
		if (cmd->is_builtin && !cmd->redir_in && !cmd->redir_out && !cmd->is_piped && !cmd->prev)
			return ((void) redir_built_ins(cmd, shell));
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
	wait_for_all(shell->cmd, shell);
	signal_handler(shell, 'P');
}
