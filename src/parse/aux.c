/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:21:45 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/04 12:31:32 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_expand_zones(char *input)
{
	int		count;
	t_bool	quote;
	t_bool	d_quote;

	if (!input)
		return (0);
	count = 0;
	init_proc(NULL, NULL, &quote, &d_quote);
	while (*input)
	{
		check_char_quote((const char **)&input, &quote, &d_quote);
		if (!quote && !d_quote && *input == '$' && is_quotes(*(input + 1)))
			count++;
		input++;
	}
	return (count);
}

void	check_quote_spaces(const char **s, t_bool *quote, t_bool *d_quote)
{
	if (!s)
		return ;
	check_quotes(**s, quote, d_quote);
	if (**s == '\\' && *(*s + 1) && is_quotes(*(*s + 1)))
	{
		*quote = FALSE;
		*d_quote = FALSE;
	}
}

char	*remove_zones(char **ptr, char *input)
{
	char	*output;
	t_bool	quote;
	t_bool	d_quote;
	int		i;

	if (!ptr || !input)
		return (NULL);
	output = malloc(ft_strlen(input) - count_expand_zones(input) + 1);
	if (!output)
		return (merror("remove_zones"), NULL);
	i = 0;
	init_proc(NULL, NULL, &quote, &d_quote);
	while (*input)
	{
		check_char_quote((const char **)&input, &quote, &d_quote);
		if (!(!quote && !d_quote && *input == '$' && is_quotes(*(input + 1))))
			output[i++] = *input;
		input++;
	}
	output[i] = '\0';
	free(*ptr);
	return (output);
}

char	*get_full_path(char *cmd, char **envp)
{
	char	**path;
	char	*temp;
	int		i;

	if (cmd && ft_strcmp(cmd, "") && ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path = ft_getenv(envp, "PATH", ':', &get_hell(NULL)->fmalloc);
	if (!path)
		return (NULL);
	i = -1;
	while (cmd && ft_strcmp(cmd, "") && ft_strcmp(cmd, "..") && path[++i])
	{
		temp = ft_strjoin(path[i], cmd);
		if (!temp)
			return (merror("get_full_path:temp"), ft_clean_matrix(path), NULL);
		if (temp && access(temp, X_OK) == 0)
			return (ft_clean_matrix(path), temp);
		free(temp);
	}
	return (ft_clean_matrix(path), NULL);
}

t_bool	check_ambiguous(t_token *tok)
{
	int	i;

	if (!tok)
		return (TRUE);
	while (tok)
	{
		i = 0;
		if (tok->expanded)
		{
			if (tok->type == INFILE || tok->type == OUTFILE_APPEND
				|| tok->type == OUTFILE)
			{
				ft_count(tok->cmd, &i);
				if (i != 1)
				{
					get_hell(NULL)->status = 1;
					return (error_ambiguous(tok->backup), TRUE);
				}
			}
		}
		tok = tok->next;
	}
	return (FALSE);
}
