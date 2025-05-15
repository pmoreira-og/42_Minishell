/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:40:54 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/15 13:54:31 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_word(const char *start, const char *end)
{
	char	*word;
	int		i;

	if (!start || !end)
		return (NULL);
	i = 0;
	word = (char *)malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i++] = *start;
		start++;
	}
	word[i] = '\0';
	return (word);
}

static char	*get_env_value(t_env **env, char *name)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, name))
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("");
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

char	*expand_vars(char *s, char *end, t_env **env)
{
	char	*start;
	char	*result;
	char	*temp;

	result = NULL;
	while (s < end)
	{
		if (*s == '$')
		{
			start = ++s;
			while ((s < end) && *s && (ft_isalnum(*s) || *s == '_'))
				s++;
			temp = new_word(start, s);
			result = ft_expand(result, (get_env_value(env, temp)), &temp);
		}
		else
		{
			start = s;
			while ((s < end) && *s && *s != '$')
				s++;
			temp = new_word(start, s);
			result = ft_expand(result, temp, NULL);
		}
	}
	return (result);
}

void	ft_copy(char **output, char *s, char **ptr)
{
	char	*tmp;
	char	*end_quote;

	if (!output || !s || !ptr)
		return ;
	end_quote = ft_strchr(s + 1, '\'');
	if (end_quote)
	{
		tmp = new_word(s, ft_strchr(s + 1, '\''));
		*output = ft_expand(*output, tmp, &tmp);
		*ptr = ft_strchr(tmp + 1, '\'') + 1;
	}
}
