/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:36:02 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/22 13:22:42 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_size(t_token *start, t_token **save_ptr, int *cmd_c, t_bool *flag)
{
	t_token	*temp;
	int		count;

	if (!start)
		return (0);
	temp = start;
	count = 0;
	while (temp->next && temp->type != PIPE)
	{
		if ((temp->type == ARG) || (temp->type == BUILT_IN)
			|| (temp->type == CMD))
			count++;
		temp = temp->next;
	}
	if (save_ptr && temp->type == PIPE && temp->next)
	{
		*save_ptr = temp->next;
		if (flag)
			*flag = TRUE;
	}
	else if (save_ptr)
		*save_ptr = temp->next;
	if (cmd_c)
		*cmd_c += 1;
	return (count);
}

char	**build_args(t_token *start, t_cmd **cmd)
{
	char	**args;
	int		i;
	t_token	*temp;

	if (!start)
		return (NULL);
	(*cmd)->argc = command_size(start, &temp, NULL, &(*cmd)->is_piped);
	args = ft_calloc((*cmd)->argc + 1, sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (start->next && start->type != PIPE)
	{
		if ((start->type == ARG) || (start->type == BUILT_IN)
			|| (start->type == CMD))
			args[i++] = ft_strdup(start->cmd);
		start = start->next;
	}
	return (args);
}

void	fill_cmd(t_cmd **cmd, t_token *start)
{
	(*cmd)->args = build_args(start, cmd);
	if (!(*cmd)->args)
		return ((void) printf("DEU RUIM"));
	if ((*cmd)->args[0])
		(*cmd)->is_builtin = is_builtin((*cmd)->args[0]);
}

void	init_cmds(t_hell *data)
{
	t_token	*temp;
	t_cmd	*cmd_tmp;

	if (!data->tokens)
		return ;
	temp = data->tokens;
	data->cmd = ft_calloc(1, sizeof(t_cmd));
	if (!data->cmd)
		return ;
	cmd_tmp = data->cmd;
	while (temp)
	{
		cmd_tmp->next = ft_calloc(1, sizeof(t_cmd));
		if (!cmd_tmp->next)
			return ;
		fill_cmd(&cmd_tmp, temp);
		command_size(temp, &temp, &data->cmd_count, NULL);
		cmd_tmp = cmd_tmp->next;
	}
}
