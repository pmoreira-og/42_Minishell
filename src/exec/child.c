/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:20:53 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/17 13:24:53 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_cmd *cmd, t_hell *shell)
{
	int	flag;

	flag = 0;
	if (!ft_strcmp(cmd->args[0], "echo") && ++flag)
		return (mini_echo(cmd, &shell->env, shell));
	else if (!ft_strcmp(cmd->args[0], "pwd") && ++flag)
		return (mini_pwd(cmd));
	else if (!ft_strcmp(cmd->args[0], "cd") && ++flag)
		mini_cd(cmd, &shell->env, shell);
	else if (!ft_strcmp(cmd->args[0], "env") && ++flag)
		mini_env(shell);
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

void	execute_child(t_cmd *cmd, int prev_pipe_fd, \
	int *pipefd, t_hell *shell)
{
	signal_handler(shell, 'D');
	if (shell->hist_fd >= 0)
		close(shell->hist_fd);
	if (prev_pipe_fd != -1)
	{
		dup2(prev_pipe_fd, STDIN_FILENO);
		close(prev_pipe_fd);
	}
	if (cmd->is_piped)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	handle_redirections(cmd);
	if (cmd->is_builtin)
		mini_cleaner(NULL, shell, execute_builtin(cmd, shell));
	if (!cmd->cmd_path && cmd->args[0])
	{
		ft_printf_fd(2, "Command '%s' not found\n", cmd->args[0]);
		shell->status = 127;
	}
	if (cmd->cmd_path && cmd->args[0])
		execve(cmd->cmd_path, cmd->args, cmd->envp);
	mini_cleaner(NULL, shell, shell->status);
}
