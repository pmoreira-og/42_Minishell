/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:01:00 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/26 11:44:43 by pmoreira         ###   ########.fr       */
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

void	print_redirs(t_cmd *cmd)
{
	t_redirection	*temp;

	if (!cmd)
		return ;
	temp = cmd->redirs;
	printf("Redir_ins:\n");
	while (temp)
	{
		if (temp->type == INFILE)
			printf("[%s]:%s\n", get_type(temp->type), temp->filename);
		else if (temp->type == LIM)
			printf("[%s]:%s\n", get_type(temp->type), temp->limiter);
		temp = temp->next;
	}
	temp = cmd->redirs;
	printf("Redir_outs:\n");
	while (temp)
	{
		if (temp->type == OUTFILE || temp->type == OUTFILE_APPEND)
			printf("[%s]:%s\n", get_type(temp->type), temp->filename);
		temp = temp->next;
	}
}

void	print_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ((void) printf("(null)"));
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
	while (temp)
	{
		printf("------------CMD[%d] PID[%d]-------------\n", i + 1, temp->pid);
		printf("ARGC=%d\nARGS:\n", temp->argc);
		print_matrix(temp->args);
		printf("Pipe bool: %d\n", temp->is_piped);
		printf("Built-in bool: %d\n", temp->is_builtin);
		printf("Full_cmd_path:%s\n", temp->cmd_path);
		print_redirs(temp);
		printf("----------------------------------------\n");
		temp = temp->next;
		i++;
	}
}
