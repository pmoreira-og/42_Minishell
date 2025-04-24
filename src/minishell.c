/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:17:06 by ernda-si          #+#    #+#             */
/*   Updated: 2025/04/24 16:40:19 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	is_builtin(t_cmd cmd)
// {
// 	if (!ft_strcmp(cmd.argv[0], "echo"))
// 		return (1);
// 	else if (!ft_strcmp(cmd.argv[0], "pwd"))
// 		return (1);
// 	else if (!ft_strcmp(cmd.argv[0], "cd"))
// 		return (1);
// 	return (0);
// }

// static void	list_builtin(t_cmd cmd)
// {
// 	if (!ft_strcmp(cmd.argv[0], "echo"))
// 		echo(cmd);
// 	else if (!ft_strcmp(cmd.argv[0], "pwd"))
// 		pwd(cmd);
// 	else if (!ft_strcmp(cmd.argv[0], "cd"))
// 		cd(cmd);
// }

int	main(int ac, char **av)
{
	char	*input;
	t_cmd	cmd;

	(void)ac;
	(void)av;
	input = "";
	cmd.argv = NULL;
	cmd.argc = ac;
	if (ac == 2 && !ft_strcmp(av[1], "-b"))
		printascii();
	if(!get_history_fd(&cmd))
		load_history(&cmd);
	while (strcmp(input, "exit"))
	{
		input = readline("Minishell$ ");
		print_input(input);
		save_history(input, &cmd);
		// cmd.argv = ft_split(input, ' ');
		// if (is_builtin(cmd) && cmd.argv[0])
		// 	list_builtin(cmd);
	}
	free(input);
	return (0);
}
