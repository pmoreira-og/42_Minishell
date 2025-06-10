/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:17:06 by ernda-si          #+#    #+#             */
/*   Updated: 2025/06/10 11:49:40 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_builtin(t_hell *hell)
{
	if (!ft_strcmp(hell->cmd->args[0], "echo"))
		mini_echo(hell->cmd, &hell->env);
	else if (!ft_strcmp(hell->cmd->args[0], "pwd"))
		mini_pwd(hell->cmd);
	else if (!ft_strcmp(hell->cmd->args[0], "cd"))
		mini_cd(hell->cmd, &hell->env);
	else if (!ft_strcmp(hell->cmd->args[0], "env"))
		mini_env(hell->env);
	else if (!ft_strcmp(hell->cmd->args[0], "exit"))
		mini_exit(hell);
	else if (!ft_strcmp(hell->cmd->args[0], "export"))
		mini_export(&hell->env, &hell->export, hell->cmd);
	else if (!ft_strcmp(hell->cmd->args[0], "unset"))
		mini_unset(&hell->env, hell->cmd);
}

int	lst_size(t_cmd *cmd)
{
	int		size;
	t_cmd	*temp;

	size = 0;
	temp = cmd;
	while (temp -> next)
	{
		size++;
		temp = temp->next;
	}
	printf("lst size: %d\n", size);
	return (size);
}

static void	init_exec(t_hell *hell)
{
	if (hell->debug)
		printf(RED"------RUNNING EXEC PART NOW-----------\n"RESET);
	if (hell->cmd && hell->cmd->args[0] && is_builtin(hell->cmd->args[0]))
		list_builtin(hell);
	// else
	// 	execute_pipeline(hell);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_hell	*hell;

	input = "";
	hell = init_hell(ac, av, envp);
	if (!hell)
		return (1);
	while (1)
	{
		input = readline(RED"Minishell>"RESET);
		save_history(input, hell);
		parser(&input, hell);
		if (hell->cmd)
			init_exec(hell);
		prepare_next_input(hell);
		free(input);
	}
	armageddon(hell);
	return (0);
}
