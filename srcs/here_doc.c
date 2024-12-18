/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:20:53 by wzeraig           #+#    #+#             */
/*   Updated: 2024/12/18 10:57:06 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	read_and_write(int HD, char *limiteur, t_all *all, t_redir *redir)
{
	char	*str;

	str = NULL;
	while (1)
	{
		str = readline("> ");
		if (str == NULL && g_sig == SIGINT)
		{
			if (all->fd_in)
			{
				dup2(all->fd_in, STDIN_FILENO);
				if (!redir->next)
					close(all->fd_in);
			}
			return (2);
		}
		if (str == NULL)
			return (1);
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

	all->fd_in = dup(STDIN_FILENO); /// 1
	file_name = limiteur;
	redir->fd_here_doc = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (redir->fd_here_doc < 0)
	{
		close(redir->fd_here_doc);
		return (ft_final(all, NULL, ERR_FD, 1));
	}
	ft_sig_heredoc();
	if (read_and_write(redir->fd_here_doc, limiteur, all, redir) == 1)
		return (close(redir->fd_here_doc), ERR_READ);
	close(redir->fd_here_doc);
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
				if (heredoc(all, redir, redir->file_name) == 1)
					return (printf("heredoc = 1"), ft_final(all, NULL, NULL,
							1));
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