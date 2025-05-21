/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:59:37 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/21 16:02:50 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_str(char **ptr, char *s, t_hell *hell)
{
	char	*output;
	char	*end;
	size_t	size;

	if (!s || !hell)
		return ;
	output = NULL;
	if (!ft_strcmp(s, "$"))
	{
		*ptr = ft_strdup(s);
		return ;
	}
	size = ft_strlen(s);
	end = &s[size - 1];
	literal(&output, s, end + 1, hell);
	if (!output)
		return ;
	if (!ft_strcmp(s, "\"") || !ft_strcmp(s, "\'"))
		*ptr = output;
	else
		*ptr = remove_quotes(output);
}

void	parser(char *input, t_hell *data)
{
	tokenize(input, data);
	valid_input(data->tokens);
	init_cmds(data);
	// print_cmd_info(data);
}
