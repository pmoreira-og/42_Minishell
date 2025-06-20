/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:17:06 by ernda-si          #+#    #+#             */
/*   Updated: 2025/06/20 13:29:33 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Get the address of the memory allocated of the main struct.
/// @param hell Pointer to main struct to save or NULL to get the address.
/// @return NULL or Pointer to main struct.
t_hell	*get_hell(t_hell *hell)
{
	static t_hell	*addr;

	if (hell)
	{
		addr = hell;
		return (NULL);
	}
	else
		return (addr);
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
	{
		printf(ORANGE"--------RUNNING EXEC PART NOW-----------"RESET);
		printf("\n");
	}
	execute_pipeline(hell);
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
		hell->lines++;
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
