/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:17:06 by ernda-si          #+#    #+#             */
/*   Updated: 2025/05/28 13:33:24 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	list_builtin(t_hell *hell)
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

// static char **list_env_matrix(t_env *env)
// {
// 	char	**matrix;
// 	t_env	*temp;
// 	char	*str;
// 	int		i;

// 	matrix = ft_split("", '\0');
// 	temp = env;
// 	str = ft_strdup("");
// 	i = 0;
// 	while (temp)
// 	{
// 		str = ft_strjoin(env->var, "=");
// 		matrix[i] = ft_strjoin(str, env->value);
// 		free(str);
// 		temp = temp->next;
// 	}
// 	return (matrix);
// }

static void	init_exec(t_hell *hell)
{
	if (hell->debug)
		printf(RED"------RUNNING EXEC PART NOW-----------\n"RESET);
	if (hell->cmd && hell->cmd->args[0] && is_builtin(hell->cmd->args[0]))
		list_builtin(hell);
	else
		return ;// pipex(4, hell->cmd->args, list_env_matrix(hell->env));
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
		input = readline(RED"Minishell> "RESET);
		save_history(input, hell);
		parser(&input, hell);
		if (!ft_strcmp(input, "exit"))
			mini_exit(hell);
		// hell->cmd->args = ft_split(input, ' ');
		if (hell->cmd)
			init_exec(hell);
		prepare_next_input(hell);
		free(input);
	}
	armageddon(hell);
	return (0);
}
