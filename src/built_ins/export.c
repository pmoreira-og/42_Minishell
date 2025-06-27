/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:07:18 by ernda-si          #+#    #+#             */
/*   Updated: 2025/06/27 15:35:53 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	identifier_check(char **matrix)
{
	int	i;

	i = 0;
	if (ft_isspace(matrix[0][i]) || (!ft_isalpha(matrix[0][i]) \
	&& matrix[0][i] != '_'))
		return (0);
	while (matrix[0][i])
	{
		if (ft_isspace(matrix[0][i]) || (!ft_isalnum(matrix[0][i]) \
		&& matrix[0][i] != '_'))
			return (0);
		i++;
	}
	return (1);
}

void	sort_export_list(t_export *head, int *sorted)
{
	t_export	*curr;
	char		*tmp_var;
	char		*tmp_val;

	if (!head)
		return ;
	while (!*sorted)
	{
		*sorted = 1;
		curr = head;
		while (curr && curr->next)
		{
			if (ft_strcmp(curr->var, curr->next->var) > 0)
			{
				tmp_var = curr->var;
				tmp_val = curr->value;
				curr->var = curr->next->var;
				curr->value = curr->next->value;
				curr->next->var = tmp_var;
				curr->next->value = tmp_val;
				*sorted = 0;
			}
			curr = curr->next;
		}
	}
}

static void	print_export(t_export *export)
{
	t_export	*temp;
	int			sorted;

	temp = export;
	sorted = 0;
	sort_export_list(temp, &sorted);
	while (temp)
	{
		if (!temp->value)
			ft_printf_fd(1, "declare -x %s\n", temp->var);
		else if (temp->value && !ft_strcmp(temp->value, ""))
			ft_printf_fd(1, "declare -x %s=\"\"\n", temp->var);
		else
		{
			ft_printf_fd(1, "declare -x %s=", temp->var);
			ft_printf_fd(1, "\"%s\"\n", temp->value);
		}
		temp = temp->next;
	}
	return ;
}

int	mini_export(t_env **env, t_export **export, t_cmd *cmd)
{
	int		i;
	int		flag;
	char	**m;

	flag = 0;
	i = 1;
	if (cmd->argc == 1)
		return (print_export(*export), 0);
	while (i < cmd->argc)
	{
		m = ft_split_once(cmd->args[i], '=');
		if (!identifier_check(m) && ++flag)
			ft_printf_fd(2,
				"minishell: export: `%s': not a valid identifier\n",
				cmd->args[i]);
		ft_setexport(export, m[0], m[1]);
		if (m[0] && m[1])
			ft_setenv(env, m[0], m[1]);
		else if (m[1] && !ft_strcmp(m[1], ""))
			(ft_setenv(env, m[0], ""), ft_setexport(export, m[0], "\"\""));
		ft_clean_matrix(m);
		i++;
	}
	update_env(get_hell(NULL));
	return (flag != 0);
}
