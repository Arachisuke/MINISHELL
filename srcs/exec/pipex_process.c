/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:29:10 by macos             #+#    #+#             */
/*   Updated: 2024/11/21 13:33:24 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	first_process(t_all *all, t_pipex *pipex, t_simple_cmds *cmds)
{
	if (dup2(all->pipex->pipefd[0][0], STDIN_FILENO) < 0)
		return (ft_errchild(all, " first process stdout", pipex, 127));
	if (dup2(all->pipex->pipefd[0][1], STDOUT_FILENO) < 0)
		return (ft_errchild(all, " first process stdout", pipex, 127));
	open_and_close(all, cmds, pipex);
	close_fd(pipex, cmds); // pipefd, et les deux fd de cmds.
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
	return (0);
}

int	process_final(t_all *all, t_pipex *pipex, t_simple_cmds *cmds)
{
	int	i;

	i = -1;
	if (dup2(all->pipex->pipefd[pipex->nbrcmd - 2][0], STDIN_FILENO) < 0)
		return (ft_errchild(all, " first process stdout", pipex, 127));
	while (++i < pipex->nbrcmd - 1)
		cmds = cmds->next;
	if (!cmds)
		return (0);
	open_and_close(all, cmds, pipex);
	close_fd(pipex, cmds); // pipefd, et les deux fd de cmds.
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
	return (0);
}

int	create_process(t_all *all, t_pipex *pipex, t_simple_cmds *cmds)
{
	int	i;
	int	j;

	j = 1;
	i = 1;
	cmds = cmds->next;
	while (pipex->nbrcmd > i + 1)
	{
		pipex->pid[i] = fork();
		if (pipex->pid[i] == -1)
			return (ft_errchild(all, "fork", pipex, 1));
		if (pipex->pid[i] == 0 && pipex->pid[i - 1] > 0)
			process_middle(all, cmds, i);
		cmds = cmds->next;
		i++;
	}
	return (0);
}

int	process_middle(t_all *all, t_simple_cmds *cmds, int i)
{
	if (!cmds)
		return (0);
	if (dup2(all->pipex->pipefd[i - 1][0], STDIN_FILENO) < 0)
		return (ft_errchild(all, "middle dup23", all->pipex, 1));
	if (dup2(all->pipex->pipefd[i][1], STDOUT_FILENO) < 0)
		return (ft_errchild(all, " middle dup31", all->pipex, 1));
	open_and_close(all, cmds, all->pipex);
	close_fd(all->pipex, cmds); // pipefd, et les deux fd de cmds.
	if (cmds->is_builtin)
	{
		builtins_or_not(all, cmds);
		return(ft_errchild(all, NULL, all->pipex, 0));
	}
	else
	{
		all->pipex->path = checkcmd(all, all->pipex->all_path, cmds->strs[0],
				all->pipex);
		if (!all->pipex->path)
			return (ft_errchild(all, "Command not found", all->pipex, 127));
		execve(all->pipex->path, cmds->strs, all->pipex->env);
		return (ft_errchild(all, "execve", all->pipex, 1));
	}
	return (0);
}

int	init_variable(t_pipex *pipex, t_all *all)
{
	int	i;

	i = 0;
	while (pipex->nbrcmd - 1 > i)
	{
		pipex->pipefd[i] = malloc(sizeof(int) * 2);
		if (pipex->pipefd[i] == NULL)
			return (ft_errchild(all, "malloc1", pipex, 1));
		pipex->pipefd[i][0] = 0;
		pipex->pipefd[i][1] = 0;
		i++;
	}
	i = 0;
	while (pipex->nbrcmd - 1 > i)
	{
		if (pipe(pipex->pipefd[i]) < 0)
			return (ft_errchild(all, "pipe", pipex, 1));
		i++;
	}
	return (0);
}
