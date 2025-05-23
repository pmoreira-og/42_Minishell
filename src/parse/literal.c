/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:06:07 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/23 15:18:00 by pmoreira         ###   ########.fr       */
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

void	ft_append(t_expand *t, t_hell *hell)
{
	char	*temp;
	char	**ptr;

	if (t->flag == FALSE)
	{
		temp = expand_vars_test(t->start, t->end, hell);
	}
	else
	{
		temp = new_word(t->start, t->end);
	}
	ptr = t->ptr;
	*ptr = ft_expand(*ptr, temp, &temp);
}

// void	literal(char **ptr, char *s, char *endptr, t_hell *hell)
// {
// 	// char		*temp;
// 	char		*start;
// 	char		*end;
// 	t_expand	tmp;

// 	while(s < endptr)
// 	{
// 		find_non_expand(s, &start, &end);
// 		if (start && end && start > s)
// 			init_expand(&tmp, ptr, s, start);
// 		else if (start && end)
// 		{
// 			init_expand(&tmp, ptr, s, start);
// 			tmp.flag = TRUE;
// 			if (*end)
// 		}
// 		else
// 			init_expand(&tmp, ptr, s, endptr);
// 		ft_append(&tmp, hell);
// 		if (*end && end < endptr)
// 			s = end;
// 	}
// }

// void	literal(char **ptr, char *s, char *endptr, t_hell *hell)
// {
// 	char	*start;
// 	char	*end;
// 	char	*temp;
// 	// char	*rest;

// 	find_non_expand(s, &start, &end);
// 	if (start && end)
// 	{
// 		if (start > s && *(start - 1) && *(start - 1) != '$')
// 			*ptr = expand_vars_test(s, start, hell);
// 		else if (start > s && *(start - 1))
// 			*ptr = expand_vars_test(s, start - 1, hell);
// 		temp = (new_word(start, end));
// 		printf("TEMP:%s\n",temp);
// 		*ptr = (ft_expand(*ptr, temp, &temp));
// 		if (*(end))
// 		{
// 			printf("Rest:%s\n", end);
// 			literal(&temp, end, endptr, hell);
// 			*ptr = (ft_expand(*ptr, temp, &temp));
// 		}
// 	}
// 	else
// 		*ptr = expand_vars_test(s, endptr, hell);
// }

void	literal(char **ptr, char *s, char *endptr, t_hell *hell)
{
	char	*start;
	char	*end;
	char	*temp;

	while (s < endptr)
	{
		find_non_expand(s, &start, &end);
		if (!start || !end)
		{
			temp = expand_vars_test(s, endptr, hell);
			*ptr = ft_expand(*ptr, temp, &temp);
			break;
		}
		if (start > s)
		{
			temp = expand_vars_test(s, start, hell);
			*ptr = ft_expand(*ptr, temp, &temp);
		}
		temp = new_word(start, end);
		*ptr = ft_expand(*ptr, temp, &temp);
		s = end;
		if (*s == '\0')
			break;
	}
}
