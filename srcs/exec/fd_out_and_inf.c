/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_out_and_inf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:39:37 by wzeraig           #+#    #+#             */
/*   Updated: 2024/11/13 12:30:28 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// A REDUIRE !!!
int	fd_out_and_inf(t_all *all, t_simple_cmds *cmds, t_redir *redir, int fd)
{
	t_redir	*last_infile;
	t_redir	*last_outfile;

	last_infile = NULL;
	last_outfile = NULL;
	redir = cmds->redir;
	if (!redir)
		return ;
	while (redir)
	{
		if (redir->token == GREATER || redir->token == D_GREATER)
		{
			last_outfile = redir;
			if (cmds->fd_outfile > 0)
			{
				close(cmds->fd_outfile);
				cmds->fd_outfile = 0;
			}
			if (last_outfile->token == GREATER)
				cmds->fd_outfile = open(last_outfile->file_name,
						O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else if (last_outfile->token == D_GREATER)
				cmds->fd_outfile = open(last_outfile,
						O_WRONLY | O_APPEND | O_CREAT, 0644);
		}
		else if (redir->token == LOWER || redir->token == D_LOWER)
			last_infile = redir;
		redir = redir->next;
	}
	if (last_outfile)
	{
		if (dup2(cmds->fd_outfile, STDOUT_FILENO) < 0)
			return(ft_error(all, " first process stdout", pipex, 127));
	}
	if (last_infile)
	{
		if (last_infile->token == D_LOWER)
		{
			last_infile->fd_here_doc = open(last_infile->file_name, O_RDONLY);
			if (last_infile->fd_here_doc < 0)
				return(ft_error(all, " first process heredoc", pipex, 127));
			if (dup2(last_infile->fd_here_doc, STDIN_FILENO) < 0)
				return(ft_error(all, " first process stdin", pipex, 127));
			close(last_infile->fd_here_doc);
		}
		else if (last_infile->token == LOWER)
		{
			cmds->fd_infile = open(last_infile->file_name, O_RDONLY);
			if (cmds->fd_infile < 0)
				return(ft_error(all, " first process stdin", pipex, 127));
			if (dup2(cmds->fd_infile, STDIN_FILENO) < 0)
				return(ft_error(all, " first process stdin", pipex, 127));
		}
	}
}
