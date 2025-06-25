/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ernda-si <ernda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:36:02 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/25 15:53:39 by ernda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	valid_arg(t_token *tok)
{
	t_bool	invalid;

	if (!tok)
		return (FALSE);
	invalid = tok->expanded && !ft_strcmp(tok->cmd, "");
	if (invalid)
		return (FALSE);
	return (TRUE);
}

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
		if (((temp->type == ARG) || (temp->type == BUILT_IN)
				|| (temp->type == CMD)) && valid_arg(temp))
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
		return (merror("build_args:matrix"), NULL);
	i = 0;
	while (start->next && start->type != PIPE)
	{
		if (((start->type == ARG) || (start->type == BUILT_IN)
				|| (start->type == CMD)) && valid_arg(start))
		{
			args[i] = ft_strdup(start->cmd);
			if (!args[i])
				return (merror("build_args:arg"), ft_free(args, ++i));
			i++;
		}
		start = start->next;
	}
	return (args);
}

int	fill_cmd(t_cmd **cmd, t_token *start, t_hell *data)
{
	(*cmd)->args = build_args(start, cmd);
	if (!(*cmd)->args)
		return (0);
	if ((*cmd)->args[0])
		(*cmd)->is_builtin = is_builtin((*cmd)->args[0]);
	if (!init_redirs(cmd, start))
		return (0);
	(*cmd)->envp = copy_env(data->envp);
	if (!(*cmd)->envp)
		return (0);
	if (!(*cmd)->is_builtin)
		(*cmd)->cmd_path = get_full_path((*cmd)->args[0], (*cmd)->envp);
	(*cmd)->fd_in = STDIN_FILENO;
	(*cmd)->fd_out = STDOUT_FILENO;
	return (1);
}

void	init_cmds(t_hell *data)
{
	t_token	*temp;
	t_cmd	*cmd_tmp;
	t_cmd	*last;

	if (!data->tokens)
		return ;
	cmd_tmp = NULL;
	last = NULL;
	temp = data->tokens;
	data->cmd = NULL;
	while (temp)
	{
		cmd_tmp = ft_calloc(1, sizeof(t_cmd));
		if (!cmd_tmp)
			return (merror("init_cmds:struct"), armageddon(data));
		if (!fill_cmd(&cmd_tmp, temp, data))
			return (merror("init_cmds:fill_cmd"), armageddon(data));
		command_size(temp, &temp, &data->cmd_count, NULL);
		if (!data->cmd)
			data->cmd = cmd_tmp;
		else
			last->next = cmd_tmp;
		last = cmd_tmp;
	}
	update_prev_cmd(data->cmd);
}
