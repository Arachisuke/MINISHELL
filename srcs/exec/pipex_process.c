/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:29:10 by macos             #+#    #+#             */
/*   Updated: 2024/11/12 15:41:35 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	first_process(t_all *all, t_pipex *pipex, t_simple_cmds *cmds,
		char **envp)
{
	//  appel de fdoutandinf if (la fonction renvoie 0) ->
	if (dup2(all->pipex->pipefd[0][1], STDOUT_FILENO) < 0)
		ft_error(all, " first process stdout", 127);
	close_fd(data->argc_copy, data); // close all fd
	if (cmds->is_builtin)            // apres avoir ouvert les fd
		builtins_or_not(all, cmds);
	else
	{
		data->path = checkcmd(data->all_path, *data->cmd, data);
		if (!data->path)
			ft_error(data, "Command not found", 127);
		execve(data->path, cmds->strs, envp);
		ft_error(data, "execve", 1);
	}
}

void	process_final(t_all *all, t_pipex *pipex,  char **argv, int argc)
{
	//  appel de fdoutandinf if (la fonction renvoie 0) ->
	if (dup2(all->pipex->pipefd[pipex->nbrcmd - 1][1], STDOUT_FILENO) < 0)
		ft_error(all, " first process stdout", 127);
	close_fd(data->argc_copy, data); // close all fd
	if (cmds->is_builtin)            // apres avoir ouvert les fd
		builtins_or_not(all, cmds);
	else
	{
		data->path = checkcmd(data->all_path, *data->cmd, data);
		if (!data->path)
			ft_error(data, "Command not found", 127);
		execve(data->path, cmds->strs, envp);
		ft_error(data, "execve", 1);
	}
}

void	create_process(char **argv, t_data *data)
{
	int	i;
	int	j;

	j = 1;
	i = 1;
	while (data->argc_copy - (5 + data->ifhdoc) > i - 1)
	{
		data->id[i] = fork();
		if (data->id[i] == -1)
			ft_error(data, "fork", 1);
		if (data->id[i] == 0 && data->id[i - 1] > 0)
			process_middle(data, argv[i + j + 1 + data->ifhdoc], i);
		i++;
	}
}

void	process_middle(t_data *data, char *cmd, int i)
{
	if (dup2(data->pipefd[i - 1][0], STDIN_FILENO) < 0)
		ft_error(data, "middle dup23", 1);
	if (dup2(data->pipefd[i][1], STDOUT_FILENO) < 0)
		ft_error(data, " middle dup31", 1);
	close_fd(data->argc_copy, data);
	getcmd(data, cmd);
	if (!data->cmd[0])
		ft_error(data, "Command not found", 127);
	data->path = checkcmd(data->all_path, *data->cmd, data);
	if (!data->path)
		ft_error(data, "Command not found", 127);
	execve(data->path, data->cmd, data->envp_copy);
	ft_error(data, "execve", 1);
}

void	init_variable(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->nbrcmd - 1 > i)
	{
		pipex->pipefd[i] = malloc(sizeof(int) * 2);
		if (pipex->pipefd[i] == NULL)
			ft_error(pipex, "malloc1", 1);
		pipex->pipefd[i][0] = 0;
		pipex->pipefd[i][1] = 0;
		i++;
	}
	pipex->pipefd[i] = NULL;
	i = 0;
	while (pipex->nbrcmd - 1 > i)
	{
		if (pipe(pipex->pipefd[i]) < 0)
			ft_error(pipex, "pipe", 1);
		i++;
	}
}
