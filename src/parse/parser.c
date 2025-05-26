/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:59:37 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/26 11:34:26 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	process_str(char **ptr, char *s, t_hell *hell)
{
	char	*output;
	char	*start;
	char	*end;
	size_t	size;

	if (!s || !hell)
		return ;
	output = NULL;
	start = s;
	if (!ft_strcmp(s, "$"))
		return (associate(ptr, ft_strdup(s)));
	size = ft_strlen(s);
	end = &s[size - 1];
	literal(&output, start, end + 1, hell);
	if (!output)
		return ;
	if (!ft_strcmp(s, "\"") || !ft_strcmp(s, "\'"))
		*ptr = output;
	else
		*ptr = remove_quotes(output);
}

void	parser(char **input, t_hell *data)
{
	if (!quotes_check(*input))
		return (ft_putstr_fd(ERR_QUOTES, 2));
	tokenize(*input, data);
	valid_input(data->tokens);
	init_cmds(data);
	// print_cmd_info(data);
	print_token(data->tokens);
}
