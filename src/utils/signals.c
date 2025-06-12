/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:41:17 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/12 13:27:13 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Exits the Here Doc process in case of CTRL+C
static void	here_doc_sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		mini_cleaner(NULL, get_hell(NULL), 130);
	}
}

static void	parent_sig_handler(int signal)
{
	t_hell	*data;

	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		data = get_hell(NULL);
		data->status = 130;
	}
}

void	signal_handler(t_hell *hell, int flag)
{
	get_hell(hell);
	if (flag == 'H')
		signal(SIGINT, here_doc_sig_handler);
	else if (flag == 'P')
		signal(SIGINT, parent_sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
