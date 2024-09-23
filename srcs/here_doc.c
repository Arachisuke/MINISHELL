/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:20:53 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/23 17:43:49 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	heredoc(t_redir *redir, char *limiteur, int fd)
{
	char	*str;
	char	*file_name;

	file_name = limiteur;
	str = NULL;
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	while (1)
	{
		str = readline("> ");
		if (str == NULL)
			return (1);
		if (!redir->next)
		{
			fd = open(file_name, O_RDONLY);
			return (fd);
		}
		if (fd < 0)
			return (1);
		return (0);
	}
}
int	if_here_doc(t_all *all)
{
	int fd;
	t_redir *redir;
	t_simple_cmds *cmds;
	int the_fd;

	fd = 0;
	the_fd = 0;
	cmds = all->cmds;
	while (cmds)
	{
		redir = cmds->redir;
		while (redir)
		{
			if (redir->token == D_LOWER)
				the_fd = heredoc(redir, redir->file_name, fd);
			redir = redir->next;
		}
		cmds = cmds->next;
	}
	if (the_fd) // 1 // 0 // au dessus de 2
		return (9);

	return (0);
}