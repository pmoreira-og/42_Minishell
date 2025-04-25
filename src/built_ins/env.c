/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:15:18 by pmoreira          #+#    #+#             */
/*   Updated: 2025/04/25 12:15:33 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_env(t_env *env)
{
	t_env *temp;

	temp = env;
	while (temp)
	{
		printf("%s=", temp->var);
		if (temp->value)
			printf("%s\n", temp->value);
		else
			printf("\n");
		temp = temp->next;
	}
	return ;
}
