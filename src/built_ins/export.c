/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ernda-si <ernda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:07:18 by ernda-si          #+#    #+#             */
/*   Updated: 2025/06/13 14:10:02 by ernda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	identifier_check(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[0][i])
	{
		if (matrix[0][i] == ' ' || matrix[0][i] == '\t')
			return (0);
		i++;
	}
	return (1);
}

void	sort_export_list(t_export *head)
{
	t_export	*curr;
	int			sorted;
	char		*tmp_var;
	char		*tmp_val;

	sorted = 0;
	curr = head;
	tmp_var = curr->var;
	tmp_val = curr->value;
	while (!sorted)
	{
		sorted = 1;
		curr = head;
		while (curr && curr->next)
		{
			if (ft_strcmp(curr->var, curr->next->var))
			{
				tmp_var = curr->var;
				tmp_val = curr->value;
				curr->var = curr->next->var;
				curr->value = curr->next->value;
				curr->next->var = tmp_var;
				curr->next->value = tmp_val;
				sorted = 0;
			}
			curr = curr->next;
		}
	}
}

static void	print_export(t_export *export)
{
	t_export	*temp;

	temp = export;
	sort_export_list(temp);
	while (temp)
	{
		if (!temp->value)
			printf("declare -x %s\n", temp->var);
		else if (temp->value[0] == '\0')
			printf("declare -x %s=\"\"\n", temp->var);
		else
		{
			printf("declare -x %s=", temp->var);
			printf("%s\n", temp->value);
		}
		temp = temp->next;
	}
	return ;
}

void	mini_export(t_env **env, t_export **export, t_cmd *cmd)
{
	int		i;
	char	**matrix;

	i = 1;
	if (cmd->argc == 1)
		return (print_export(*export));
	while (i < cmd->argc)
	{
		matrix = ft_split_once(cmd->args[i], '=');
		if (!identifier_check(matrix))
			fprintf(stderr,
				"Minishell: export: `%s': not a valid identifier\n",
				cmd->args[i]);
		else if (matrix[0] && matrix[1])
		{
			ft_setenv(env, matrix[0], matrix[1]);
			ft_setexport(export, matrix[0], matrix[1]);
		}
		else if (matrix[0] && !matrix[1])
			ft_setexport(export, matrix[0], NULL);
		else if (!ft_strcmp(matrix[1], ""))
		{
			ft_setenv(env, matrix[0], "\"\"");
			ft_setexport(export, matrix[0], "\"\"");
		}
		ft_clean_matrix(matrix);
		i++;
	}
}
