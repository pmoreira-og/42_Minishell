/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:40:54 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/14 12:52:20 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_word(const char *start, const char *end)
{
	char	*word;
	int		i;

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
	t_env *tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, name))
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("");
}

// int	new_string(char **ptr, char *s, int flag)
// {
// 	int		quotes;
// 	char	*out;

// 	quotes = 0;
// 	while(flag && *s)
// 	{
// 		if (*s == '\"')
// 			quotes++;
// 		s++;
// 	}
// 	s = *ptr;
// 	out = malloc((ft_strlen(s) - quotes + 1));
// 	if (!out)
// 		return (0);
// 	quotes = 0;
// 	while(*s)
// 	{
// 		if (flag && *s == '\"')
// 			s++;
// 		if (*s)
// 			out[quotes++] = *s;
// 		s++;
// 	}
// 	free(*ptr);
// 	*ptr = out;
// 	return (1);
// }

static char	*ft_expand(char *s1, char *s2, char **temp)
{
	char	*tmp;
	
	tmp = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (temp)
		free(*temp);
	return (tmp);
}

static char	*expand_vars(char *s, char *end, t_env **env, int flag)
{
	char	*start;
	char	*result;
	char	*temp;

	result = NULL;
	(void) flag;
	while (s < end)
	{
		if (*s == '$')
		{
			start = ++s;
			while (*s && (ft_isalnum(*s) || *s == '_'))
				s++;
			temp = new_word(start, s);
			result = ft_expand(result, (get_env_value(env, temp)), &temp);
		}
		else
		{
			start = s;
			while (*s && *s != '$')
				s++;
			temp = new_word(start, s);
			result = ft_expand(result, temp, NULL);
		}
	}
	return (result);
}

void	literal(char **ptr, char *s, t_env **env)
{
	char	*output;
	char	*temp;
	size_t	size;

	if (!s)
		return ;
	output = NULL;
	size = ft_strlen(s);
	temp = &s[size - 1];
	while (temp != s && *temp == '\"')
		temp--;
	(void) temp;
	if (*s == '\'' && s[size - 1] == '\'')
		output = new_word(s + 1, &s[size - 1]);
	// else if (temp != s && *s == '\"' && s[size - 1] == '\"')
	// 	output = expand_vars(s + 1, &s[size - 1], env, 1);
	else
		output = expand_vars(s, &s[size], env, 1);
	if (!output)
		return ;
	*ptr = output;
}
