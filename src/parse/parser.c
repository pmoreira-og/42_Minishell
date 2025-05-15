/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:59:37 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/15 14:01:47 by pmoreira         ###   ########.fr       */
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
	while (end != s && *end == '\"')
		end--;
	end++;
	while (*s && *s == '\"')
		s++;
	literal(&output, s, end, env);
	if (!output)
		return ;
	*ptr = output;
}

void	parser(char *input, t_hell *data)
{
	tokenize(input, data);
}
