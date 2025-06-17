/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:41:17 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/17 11:04:26 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_doc_handler(int sign)
{
	if (sign == SIGINT)
	{
		printf("\n");
		mini_cleaner(NULL, get_hell(NULL), 130);
	}
}

static void	parent_handler(int sign)
{
	t_hell	*data;

	if (sign == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		data = get_hell(NULL);
		data->status = 130;
	}
}

void	stop_parent_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_handler(t_hell *hell, int flag)
{
	struct sigaction	sa;

	get_hell(hell);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	if (sigemptyset(&sa.sa_mask) != 0)
		return ;
	sigaction(SIGQUIT, &sa, NULL);
	if (flag == 'P')
		sa.sa_handler = parent_handler;
	else if (flag == 'H')
		sa.sa_handler = here_doc_handler;
	else if (flag == 'D')
		sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
}
