/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:59:37 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/21 12:38:50 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_str(char **ptr, char *s, t_env **env)
{
	char	*output;
	char	*end;
	size_t	size;

	if (!s || !env)
		return ;
	output = NULL;
	size = ft_strlen(s);
	end = &s[size - 1];
	literal(&output, s, end + 1, env);
	if (!output)
		return ;
	*ptr = remove_quotes(output);
}

void	parser(char *input, t_hell *data)
{
	tokenize(input, data);
	valid_input(data->tokens);
	init_cmds(data);
	print_cmd_info(data);
	prepare_next_input(data);
}
