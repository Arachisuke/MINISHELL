/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:20:53 by wzeraig           #+#    #+#             */
/*   Updated: 2024/12/19 13:56:48 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	read_and_write(int HD, char *limiteur, t_all *all)
{
	char	*str;

	str = NULL;
	while (1)
	{
		str = readline("> ");
		if (str == NULL && g_sig == SIGINT)
			return (dup2(all->fd_in, STDIN_FILENO), close(all->fd_in), 2);
		if (str == NULL)
			return (ft_printf_fd(1, ERR_DDOC), ft_printf_fd(1, "%s')\n",
					limiteur), 1);
		if (ft_strlen(str) == ft_strlen(limiteur))
		{
			if (!ft_strncmp(str, limiteur, ft_strlen(limiteur)))
			{
				free(str);
				break ;
			}
		}
		write(HD, str, ft_strlen(str));
		write(HD, "\n", 1);
		free(str);
	}
	return (0);
}

int	heredoc(t_all *all, t_redir *redir, char *limiteur)
{
	char	*file_name;

	all->fd_in = dup(STDIN_FILENO);
	if (all->fd_in < 0)
		return (ft_final(all, NULL, ERR_FD, 1));
	file_name = limiteur;
	redir->fd_here_doc = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (redir->fd_here_doc < 0)
	{
		close(all->fd_in);
		close(redir->fd_here_doc);
		return (ft_final(all, NULL, ERR_FD, 1));
	}
	ft_signal_heredoc();
	if (read_and_write(redir->fd_here_doc, limiteur, all) == 2)
		return (close(redir->fd_here_doc), ERR_READ);
	close(redir->fd_here_doc);
	close(all->fd_in);
	return (SUCCESS);
}

int	if_here_doc(t_all *all)
{
	t_redir			*redir;
	t_simple_cmds	*cmds;

	cmds = all->cmds;
	while (cmds)
	{
		redir = cmds->redir;
		while (redir)
		{
			if (redir->token == D_LOWER)
			{
				if (heredoc(all, redir, redir->file_name) == ERR_READ)
					return (ft_final(all, NULL, NULL, 1));
			}
			redir = redir->next;
		}
		cmds = cmds->next;
	}
	return (SUCCESS);
}

// sig heredoc
// heredoc, readline, si str == NULL et gsig == sigint
// return(1) // ppuis redup,
// et close fd_in peut etre que ca relance le prochain heredoc.
// puis close, puis relance le while, trouver le deuxieme heredoc

// heredoc, doit afficher ^C
// parent doit afficher ^C,
// parent + enfant minishell, enfant minishell ne doit pas affiche.

//