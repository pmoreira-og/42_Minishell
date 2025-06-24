/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:20:53 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/24 10:51:11 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_cmd *cmd, t_hell *shell)
{
	int	flag;

	flag = 0;
	if (!ft_strcmp(cmd->args[0], "echo") && ++flag)
		return (mini_echo(cmd));
	else if (!ft_strcmp(cmd->args[0], "pwd") && ++flag)
		return (mini_pwd(cmd));
	else if (!ft_strcmp(cmd->args[0], "cd") && ++flag)
		mini_cd(cmd, &shell->env, shell);
	else if (!ft_strcmp(cmd->args[0], "env") && ++flag)
		mini_env(shell, cmd);
	else if (!ft_strcmp(cmd->args[0], "exit") && ++flag)
		mini_exit(shell);
	else if (!ft_strcmp(cmd->args[0], "export") && ++flag)
		mini_export(&shell->env, &shell->export, cmd);
	else if (!ft_strcmp(cmd->args[0], "unset") && ++flag)
		mini_unset(&shell->env, cmd, &shell->export, shell);
	else if (flag)
		return (shell->status = EXIT_SUCCESS);
	return (shell->status = EXIT_FAILURE);
}

void	execute_child(t_cmd *cmd, int prev_pipe, int *pipes, t_hell *shell)
{
	signal_handler(shell, 'D');
	if (cmd->prev && prev_pipe != -1)
		cmd->fd_in = prev_pipe;
	if (cmd->is_piped)
		cmd->fd_out = pipes[1];
	handle_redirections(cmd);
	if (shell->hist_fd >= 0)
		close(shell->hist_fd);
	if (cmd->fd_in != 0)
		ft_dup(cmd->fd_in, 0);
	if (cmd->fd_out != 1)
		ft_dup(cmd->fd_out, 1);
	close_all();
	if (cmd->is_builtin)
		mini_cleaner(NULL, shell, execute_builtin(cmd, shell));
	if (!cmd->cmd_path && cmd->args[0])
		try_run(shell, cmd->args);
	if (cmd->cmd_path && cmd->args[0])
		execve(cmd->cmd_path, cmd->args, cmd->envp);
	mini_cleaner(NULL, shell, shell->status);
}
