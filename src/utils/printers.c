/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:01:00 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/09 11:29:37 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *toks)
{
	t_token	*temp;

	if (!toks)
		return ;
	temp = toks;
	printf("------------------Tokens------------------\n");
	while (temp->next)
	{
		printf("[%s]: %s\n", temp->cmd, get_type(temp->type));
		temp = temp->next;
	}
	printf("------------------------------------------\n");
}

void	print_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		printf("arg[%d]:%s\n", i, matrix[i]);
		i++;
	}
}

void	print_cmd_info(t_hell *data)
{
	t_cmd	*temp;
	int		i;

	if (!data->cmd)
		return ;
	temp = data->cmd;
	i = 0;
	printf("Total cmds count: %d\n", data->cmd_count);
	while (temp->next)
	{
		printf("------------CMD[%d] PID[%d]-------------\n", i + 1, temp->pid);
		printf("ARGC=%d\nARGS:\n", temp->argc);
		print_matrix(temp->args);
		printf("Pipe bool: %d\n", temp->is_piped);
		printf("Built-in bool: %d\n", temp->is_builtin);
		printf("----------------------------------------\n");
		temp = temp->next;
		i++;
	}
}
