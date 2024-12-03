/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:10:54 by wzeraig           #+#    #+#             */
/*   Updated: 2024/12/03 13:23:04 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_sig(int s)
{
	g_sig = s;
	if (wait(NULL) != -1)
	{
		if (s == SIGQUIT)
			printf("Quit (core dumped)");
		printf("\n");
	}
	else if (s == SIGINT)
	{
		printf("^C\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (s == SIGQUIT)
		g_sig = 0;
}

void	sig_heredoc(int s)
{
	g_sig = s;
	close(STDIN_FILENO);
	ft_printf_fd(2, "^C");
}

void	ft_sig_heredoc(void)
{
	struct sigaction	sig;

	sig.sa_flags = 0;
	sig.sa_handler = &sig_heredoc;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGINT, &sig, NULL);
}

void	ft_signals(void)
{
	struct sigaction	sig;

	rl_catch_signals = 0;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_RESTART;
	sig.sa_handler = &handle_sig;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}

bool	catchsignals(t_all *all)
{
	if (g_sig == SIGINT)
	{
		all->exit_code = 130;
		g_sig = 0;
		return (true);
	}
	else if (g_sig == SIGQUIT)
	{
		all->exit_code = 131;
		g_sig = 0;
		return (true);
	}
	return (false);
}