/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:40:54 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/06 18:34:52 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_expand(char *input, char *endptr, char **start, char **end)
{
	t_bool	quote;
	t_bool	d_quote;

	*start = NULL;
	*end = NULL;
	init_proc(NULL, NULL, &quote, &d_quote);
	while (input < endptr)
	{
		check_quotes(*input, &quote, &d_quote);
		if (*input && d_quote)
		{
			*start = input;
			input++;
			while (*input && (*input != '\"'))
				input++;
			if (*input == '\"')
			{
				*end = input + 1;
				return ;
			}
		}
		if (*(input))
			input++;
	}
}

void	new_word_quotes(char **ptr, char *s, char *endptr)
{
	char	*temp;
	char	*start;
	char	*end;

	while (s < end)
	{
		find_expand(s, endptr, &start, &end);
		if (!start || !end)
		{
			temp = new_word(s, endptr);
			*ptr = ft_expand(*ptr, temp, &temp);
			break ;
		}
		if (start > s)
		{
			temp = new_word(s, start);
			*ptr = ft_expand(*ptr, temp, &temp);
		}
		write(1, start, end - start);
		printf("\n");
		temp = new_word(start + 1, end - 1);
		*ptr = ft_expand(*ptr, temp, &temp);
		s = end;
		if (*s == '\0')
			break ;
	}
}

void	skip_name(char **start, char **s, char *end)
{
	if (*s < end && (isdigit(**s) || **s == '\?'))
		(*s)++;
	else if (*s < end && valid_expand(**s))
	{
		(*start)++;
		while (*s < end && valid_expand(**s))
			(*s)++;
	}
}

void	concat_expand(char **result, char **new_str, t_hell *hell)
{
	char	*temp;

	if (!ft_strncmp(*new_str, "$\?", 2))
	{
		temp = ft_itoa(hell->status);
		if (!temp)
			return ;
		if (!(*result))
			*result = ft_strdup("");
		*result = ft_expand(*result, temp, new_str);
		free(temp);
	}
	else
		*result = ft_expand(*result, (get_env(&hell->env, *new_str)), new_str);
}

// Avança 's' para depois do par de aspas se encontrar aspas em *s.
// Atualiza 's' para apontar após as aspas fechadas.
// Retorna 1 se pulou um bloco de aspas, 0 caso contrário.
int skip_quotes(const char **start, const char **s, const char *end)
{
	char	quote;

	if (**s == '\'' || **s == '"')
	{
		quote = **s;
		(*s)++; // pula a abertura
		*start = *s; // início do conteúdo dentro das aspas
		while (*s < end && **s && **s != quote)
			(*s)++;
		// agora (*s) está na aspa de fechamento ou no fim
		// Se encontrou a aspa de fechamento, pula ela também
		if (*s < end && **s == quote)
			(*s)++;
		return 1;
	}
	return 0;
}

char	*expand_vars(char *s, char *end, t_hell *hell)
{
	char	*result;
	char	*start;
	char	*temp;

	result = NULL;
	while (s < end)
	{
		start = s++;
		if (*start == '$' && *s && (valid_expand(*s) || *s == '\?'))
		{
			skip_name(&start, &s, end);
			temp = new_word(start, s);
			concat_expand(&result, &temp, hell);
		}
		else
		{
			while ((s < end) && *s && *s != '$')
				s++;
			temp = new_word(start, s);
			result = ft_expand(result, temp, &temp);
		}
	}
	return (result);
}

// void	skip_name(char **start, char **s, char *end)
// {
// 	if (*s < end && (isdigit(**s) || **s == '\?'))
// 		(*s)++;
// 	else if (*s < end && valid_expand(**s))
// 	{
// 		(*start)++;
// 		while (*s < end && valid_expand(**s))
// 			(*s)++;
// 	}
// }

// void	concat_expand(char **result, char **new_str, t_hell *hell)
// {
// 	char	*temp;

// 	if (!ft_strncmp(*new_str, "$\?", 2))
// 	{
// 		temp = ft_itoa(hell->status);
// 		if (!temp)
// 			return ;
// 		if (!(*result))
// 			*result = ft_strdup("");
// 		*result = ft_expand(*result, temp, new_str);
// 		free(temp);
// 	}
// 	else
// 		*result = ft_expand(*result, (get_env(&hell->env, *new_str)), new_str);
// }

// char	*expand_vars(char *s, char *end, t_hell *hell)
// {
// 	char	*result;
// 	char	*start;
// 	char	*temp;

// 	result = NULL;
// 	while (s < end)
// 	{
// 		start = s++;
// 		if (*start == '$' && *s && (valid_expand(*s) || *s == '\?'))
// 		{
// 			skip_name(&start, &s, end);
// 			temp = new_word(start, s);
// 			concat_expand(&result, &temp, hell);
// 		}
// 		else
// 		{
// 			while ((s < end) && *s && *s != '$')
// 				s++;
// 			temp = new_word(start, s);
// 			result = ft_expand(result, temp, &temp);
// 		}
// 	}
// 	return (result);
// }
