/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:41:17 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/13 12:07:56 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_doc_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		mini_cleaner(NULL, get_hell(NULL), 130);
	}
}

static void	parent_handler(int signal)
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
	static struct sigaction	sa;

	get_hell(hell);
	if (flag == 'P')
		sa.sa_handler = parent_handler;
	else if (flag == 'H')
		sa.sa_handler = here_doc_handler;
	else
		sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	if (sigemptyset(&sa.sa_mask) != 0)
		return ;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
