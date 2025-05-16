/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:06:07 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/16 16:32:12 by pmoreira         ###   ########.fr       */
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
			// printf("char->%s\n", &s[i]);
			count++;
		else if ((!d_quote) && s[i] == '\'')
			// printf("char->%s\n", &s[i]);
			count++;
		if (s[i])
			i++;
	}
	printf("str: %s(%lu)\ncount->%d\n", s, ft_strlen(s), count);
	printf("size:%lu\n", ft_strlen(s) - count);
	output = malloc(ft_strlen(s) - count + 1);
	if (!output)
		return (NULL);
	output[ft_strlen(s) - count] = '\0';
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
			continue;// i++; // printf("char->%s\n", &s[i++]); 
		if ((!d_quote) && s[i] == '\'')
			continue; // i++;  // printf("char->%s\n", &s[i++]);
		if (s[i])
			output[j++] = s[i];
			// i++;
	}
	printf("output:%s(%lu)\n", output, ft_strlen(output));
	free(s);
	// return (NULL);
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
				return;
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
	// char	*rest;

	find_non_expand(s, &start, &end);
	// rest = NULL;
	if (start && end)
	{
		// write(1, start, end - start);
		printf("\n");
		if(start > s)
			*ptr = expand_vars(s, start, env);
		temp = (new_word(start, end));
		*ptr = (ft_expand(*ptr, temp, &temp));
		if (*(end + 1) && (end + 1) < endptr)
		{
			literal(&temp, end, endptr, env);
			*ptr = (ft_expand(*ptr, temp, &temp));
		}
		*ptr = remove_quotes(*ptr);
	}
	else
		*ptr = remove_quotes(expand_vars(s, endptr, env));
}
