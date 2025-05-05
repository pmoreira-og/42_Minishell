/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:17:06 by ernda-si          #+#    #+#             */
/*   Updated: 2025/05/05 16:24:00 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	list_builtin(t_hell *hell)
// {
// 	if (!ft_strcmp(hell->cmd->argv[0], "echo"))
// 		mini_echo(hell->cmd, &hell->env);
// 	else if (!ft_strcmp(hell->cmd->argv[0], "pwd"))
// 		mini_pwd(hell->cmd);
// 	else if (!ft_strcmp(hell->cmd->argv[0], "cd"))
// 		mini_cd(hell->cmd, &hell->env);
// 	else if (!ft_strcmp(hell->cmd->argv[0], "env"))
// 		mini_env(hell->env);
// 	else if (!ft_strcmp(hell->cmd->argv[0], "exit"))
// 		mini_exit(hell);
// 	else if (!ft_strcmp(hell->cmd->argv[0], "export"))
// 		mini_export(&hell->env, hell->cmd);
// 	else if (!ft_strcmp(hell->cmd->argv[0], "unset"))
// 		mini_unset(&hell->env, hell->cmd);
// }

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
		input = readline("\033[1;31mMinishell$\033[0m ");
		save_history(input, hell);
		print_input(input, hell);
		hell->cmd->argv = ft_split(input, ' ');
		// if (hell->cmd->argv[0] && is_builtin(hell->cmd->argv[0]))
		// 	list_builtin(hell);
		ft_clean_matrix(hell->cmd->argv);
		free(input);
	}
	armageddon(hell);
	return (0);
}
