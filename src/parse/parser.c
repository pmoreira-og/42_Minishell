/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:59:37 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/27 15:47:21 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmds(t_token *tok)
{
	t_token	*temp;
	t_bool	expanded;

	if (!tok)
		return (1);
	temp = tok;
	expanded = FALSE;
	while (temp->next)
	{
		if (temp->expanded)
			expanded = TRUE;
		if (temp->type == CMD || temp->type == BUILT_IN)
			return (1);
		temp = temp->next;
	}
	if (expanded)
		return (0);
	return (1);
}

/// @brief Join the 2 strings, free the s1 and free the s2 if the pointer are 
///		given.
/// @param s1 Output string.
/// @param s2 Temp string.
/// @param temp Address of Temp.
/// @return Strjoin.
char	*ft_expand(char *s1, char *s2, char **temp)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (free(s1), merror("ft_expand"), NULL);
	if (s1)
		free(s1);
	if (temp && *temp)
	{
		free(*temp);
		*temp = NULL;
	}
	return (tmp);
}

void	associate(char **ptr, char *new_str)
{
	if (!ptr || !new_str)
		return ;
	*ptr = new_str;
}

void	process_str(char **ptr, char *s, t_hell *hell, t_bool *flag)
{
	char	*output;
	char	*start;
	char	*end;
	size_t	size;

	if (!s || !hell)
		return ;
	output = NULL;
	start = s;
	if (!ft_strcmp(s, "$") || (flag && *flag))
		output = handle_limiter(s, flag);
	else
	{
		size = ft_strlen(s);
		end = &s[size - 1];
		literal(&output, start, end + 1, hell);
	}
	if (!output)
		return (merror("process_str"));
	return (free(*ptr), associate(ptr, output));
}

void	parser(char **input, t_hell *data)
{
	if (!(*input))
	{
		data->status = 0;
		printf("exit\n");
		return (mini_cleaner(NULL, data, 0));
	}
	if (!ft_strcmp(*input, "") || !quotes_check(*input))
		return ;
	pre_process_input(input);
	tokenize(*input, data);
	make_backup(data->tokens);
	if (data->tokens && !valid_input(data->tokens, data))
		return ;
	if (check_ambiguous(data->tokens))
		return ;
	if (!check_cmds(data->tokens))
		recall_parser(data);
	init_cmds(data);
	if (data->debug)
	{
		printf(RED"------RUNNING PARSING PART NOW-----------\n"RESET);
		print_token(data->tokens);
		print_cmd_info(data);
	}
}
