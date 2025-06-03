/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:59:37 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/03 14:55:29 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmds(t_token *tok)
{
	t_token	*temp;

	if (!tok)
		return (1);
	temp = tok;
	while (temp->next)
	{
		if (temp->type == CMD || temp->type == BUILT_IN)
			return (1);
		temp = temp->next;
	}
	return (0);
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
	if (s1)
		free(s1);
	if (temp)
		free(*temp);
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
	if (!ft_strcmp(s, "$") || *flag)
		return ;
	size = ft_strlen(s);
	end = &s[size - 1];
	literal(&output, start, end + 1, hell);
	if (!output)
		return ;
	return (free(*ptr), associate(ptr, output));
}

void	parser(char **input, t_hell *data)
{
	if (!(*input))
	{
		data->status = 0;
		return (mini_exit(data));
	}
	if (!ft_strcmp(*input, "") || !quotes_check(*input))
		return ;
	if (count_spaces(*input))
		*input = add_spaces(input, *input);
	tokenize(*input, data);
	if (data->tokens && !valid_input(data->tokens, data))
		return ;
	if (!check_cmds(data->tokens))
		recall_parser(data);
	quotes_remover(data);
	init_cmds(data);
	if (data->debug)
	{
		printf(RED"------RUNNING PARSING PART NOW-----------\n"RESET);
		print_token(data->tokens);
		print_cmd_info(data);
	}
}
