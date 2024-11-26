/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:39:37 by wzeraig           #+#    #+#             */
/*   Updated: 2024/11/26 14:58:05 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_out_or_inf(t_pipex *pipex, t_all *all, t_redir *redir,
		t_simple_cmds *cmds)
{
	if (redir->token == GREATER || redir->token == D_GREATER)
	{
		pipex->last_outfile = redir;
		if (cmds->fd_outfile > 0)
		{
			if (close(cmds->fd_outfile) == -1)
				return (ft_errchild(all, "close", pipex, 127));
			cmds->fd_outfile = 0;
		}
		if (pipex->last_outfile->token == GREATER)
			cmds->fd_outfile = open(pipex->last_outfile->file_name,
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (pipex->last_outfile->token == D_GREATER)
			cmds->fd_outfile = open(pipex->last_outfile->file_name,
					O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (cmds->fd_outfile == -1)
			return (ft_errchild(all, "open", pipex, 127));
	}
	else if (redir->token == LOWER || redir->token == D_LOWER)
		pipex->last_infile = redir;
	return (0);
}

int	who_is_last(t_redir *last_infile, t_simple_cmds *cmds, t_all *all)
{
	if (last_infile->token == D_LOWER)
	{
		last_infile->fd_here_doc = open(last_infile->file_name, O_RDONLY);
		if (last_infile->fd_here_doc == -1)
			return (ft_errchild(all, " first process heredoc", all->pipex,
					127));
		if (dup2(last_infile->fd_here_doc, STDIN_FILENO) == -1)
			return (ft_errchild(all, " first process stdin", all->pipex, 127));
		close(last_infile->fd_here_doc);
	}
	else if (last_infile->token == LOWER)
	{
		cmds->fd_infile = open(last_infile->file_name, O_RDONLY);
		if (cmds->fd_infile == -1)
			return (ft_errchild(all, " No such file or directory", all->pipex, 127));
		if (dup2(cmds->fd_infile, STDIN_FILENO) == -1)
			return (ft_errchild(all, " first process stdin3", all->pipex, 127));
	}
	return (0);
}

int	open_and_close(t_all *all, t_simple_cmds *cmds, t_pipex *pipex)
{
	t_redir	*tmp;

	tmp = cmds->redir;
	if (!tmp)
		return (0);
	while (tmp)
	{
		if (is_out_or_inf(pipex, all, tmp, cmds))
			return (127);
		tmp = tmp->next;
	}
	if (pipex->last_outfile)
		if (dup2(cmds->fd_outfile, STDOUT_FILENO) == -1)
			return (ft_errchild(all, " first process stdout", pipex, 127));
	if (pipex->last_infile)
		if (who_is_last(pipex->last_infile, cmds, all))
			return (127);
	return (SUCCESS);
}
int	onecmd(t_all *all, t_pipex *pipex, t_simple_cmds *cmds)
{
	open_and_close(all, cmds, pipex);
	close_fd(pipex, cmds);
	if (cmds->is_builtin)
	{
		builtins_or_not(all, cmds);
		return(ft_errchild(all, NULL, pipex, 0));
	}
	else
	{
		pipex->path = checkcmd(all, pipex->all_path, cmds->strs[0], pipex);
		if (!pipex->path)
			return (ft_errchild(all, "Command not found", pipex, 127));
		execve(pipex->path, cmds->strs, pipex->env);
		return (ft_errchild(all, "execve", pipex, 1));
	}
}