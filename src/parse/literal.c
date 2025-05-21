/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:06:07 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/17 18:29:54 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*alloc_str(char *s)
{
	char	*output;
	int		count;
	int		i;
	t_bool	quote;
	t_bool	d_quote;

	if (!s)
		return (NULL);
	count = 0;
	i = 0;
	init_proc(NULL, NULL, &quote, &d_quote);
	while (s[i])
	{
		check_quotes(s[i], &quote, &d_quote);
		if ((!quote) && s[i] == '\"')
			count++;
		else if ((!d_quote) && s[i] == '\'')
			count++;
		if (s[i])
			i++;
	}
	output = ft_calloc(ft_strlen(s) - count + 1, 1);
	if (!output)
		return (NULL);
	return (output);
}

char	*remove_quotes(char *s)
{
	char	*output;
	int		i;
	int		j;
	t_bool	quote;
	t_bool	d_quote;

	i = -1;
	j = 0;
	output = alloc_str(s);
	if (!output)
		return (NULL);
	init_proc(NULL, NULL, &quote, &d_quote);
	while (s[++i])
	{
		check_quotes(s[i], &quote, &d_quote);
		if ((!quote) && s[i] == '\"')
			continue ;
		if ((!d_quote) && s[i] == '\'')
			continue ;
		if (s[i])
			output[j++] = s[i];
	}
	free(s);
	return (output);
}

void	find_non_expand(char *input, char **start, char **end)
{
	t_bool	quote;
	t_bool	d_quote;

	*start = NULL;
	*end = NULL;
	init_proc(NULL, NULL, &quote, &d_quote);
	while (*input)
	{
		check_quotes(*input, &quote, &d_quote);
		if (*input && quote)
		{
			*start = input;
			input++;
			while (*input && (*input != '\''))
				input++;
			if (*input == '\'')
			{
				*end = input + 1;
				return ;
			}
		}
		if (*(input))
			input++;
	}
}

void	literal(char **ptr, char *s, char *endptr, t_env **env)
{
	char	*start;
	char	*end;
	char	*temp;

	find_non_expand(s, &start, &end);
	if (start && end)
	{
		if (start > s)
			*ptr = expand_vars(s, start, env);
		temp = (new_word(start, end));
		*ptr = (ft_expand(*ptr, temp, &temp));
		if (*(end))
		{
			literal(&temp, end, endptr, env);
			*ptr = (ft_expand(*ptr, temp, &temp));
		}
	}
	else
		*ptr = expand_vars(s, endptr, env);
}
