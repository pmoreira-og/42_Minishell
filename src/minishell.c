/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:17:06 by ernda-si          #+#    #+#             */
/*   Updated: 2025/04/25 13:08:41 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(t_hell *hell)
{
	if (!ft_strcmp(hell->cmd->argv[0], "echo"))
		return (1);
	else if (!ft_strcmp(hell->cmd->argv[0], "pwd"))
		return (1);
	else if (!ft_strcmp(hell->cmd->argv[0], "cd"))
		return (1);
	else if (!ft_strcmp(hell->cmd->argv[0], "env"))
		return (1);
	else if (!ft_strcmp(hell->cmd->argv[0], "exit"))
		return (1);
	else if (!ft_strcmp(hell->cmd->argv[0], "export"))
		return (1);
	else if (!ft_strcmp(hell->cmd->argv[0], "unset"))
		return (1);
	return (0);
}

static void	list_builtin(t_hell *hell)
{
	if (!ft_strcmp(hell->cmd->argv[0], "echo"))
		mini_echo(hell->cmd, &hell->env);
	else if (!ft_strcmp(hell->cmd->argv[0], "pwd"))
		mini_pwd(hell->cmd);
	else if (!ft_strcmp(hell->cmd->argv[0], "cd"))
		mini_cd(hell->cmd, &hell->env);
	else if (!ft_strcmp(hell->cmd->argv[0], "env"))
		mini_env(hell->env);
	else if (!ft_strcmp(hell->cmd->argv[0], "exit"))
		mini_exit(hell);
	else if (!ft_strcmp(hell->cmd->argv[0], "export"))
		mini_export(&hell->env, hell->cmd);
	else if (!ft_strcmp(hell->cmd->argv[0], "unset"))
		mini_unset(&hell->env, hell->cmd);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_hell	*hell;

	(void)ac;
	(void)av;
	input = "";
	hell = malloc(sizeof(t_hell));
	if (!hell)
		return (1);
	hell->cmd = malloc(sizeof(t_cmd));
	if (!hell->cmd)
		return (1);
	hell->cmd->argv = NULL;
	hell->env = NULL;
	init_env(&hell->env, envp);
	if (ac == 2 && !ft_strcmp(av[1], "-b"))
		printascii();
	if (!get_history_fd(hell->cmd))
		load_history(hell->cmd);
	while (1)
	{
		input = readline("\033[1;31mMinishell$\033[0m ");
		save_history(input, hell->cmd);
		hell->cmd->argv = ft_split(input, ' ');
		if (is_builtin(hell) && hell->cmd->argv[0])
			list_builtin(hell);
		ft_clean_matrix(hell->cmd->argv);
		free(input);
	}
	// free_shell(hell); // free_cmd, free_env, etc.
	return (0);
}
