/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:19:37 by wzeraig           #+#    #+#             */
/*   Updated: 2024/12/19 14:01:07 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_sig(int s)
{
	g_sig = s;
	if (wait(NULL) != -1)
	{
		if (s == SIGQUIT)
			printf("Quit (core dumped)1");
		printf("\n");
	}
	else if (s == SIGINT)
	{
		ft_printf_fd(1, "^C\n");
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
	ft_printf_fd(2, "^C");
	close(STDIN_FILENO);
}

void	ft_nosignals(void)

{
	struct sigaction	sa;

	rl_catch_signals = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
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
