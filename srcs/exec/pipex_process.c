/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:29:10 by macos             #+#    #+#             */
/*   Updated: 2024/11/11 15:30:45 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	first_process(t_data *data, char **argv, char **envp)
{
	if (data->ifhdoc)
	{
		if (dup2(data->heredoc, STDIN_FILENO) < 0)
			ft_error(data, " first process stdin1", 127);
	}
	else
	{
		data->infile = open(argv[1], O_RDONLY, 0644);
		if (data->infile == -1)
			ft_error(data, "Permission denied", 127);
		if (dup2(data->infile, STDIN_FILENO) < 0)
			ft_error(data, " first process stdin", 127);
	}
	if (dup2(data->pipefd[0][1], STDOUT_FILENO) < 0)
		ft_error(data, " first process stdout", 127);
	close_fd(data->argc_copy, data);
	getcmd(data, argv[2 + data->ifhdoc]);
	if (!data->cmd[0])
		ft_error(data, "Command not found", 127);
	data->path = checkcmd(data->all_path, *data->cmd, data);
	if (!data->path)
		ft_error(data, "Command not found", 127);
	execve(data->path, data->cmd, envp);
	ft_error(data, "execve", 1);
}

void	process_final(t_data *data, char **argv, int argc)
{
	if (data->heredoc && argc == 5)
		return ;
	if (data->heredoc)
		data->outf = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		data->outf = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (data->outf == -1)
		ft_error(data, "Permission denied", 1);
	if (dup2(data->pipefd[argc - 5 - data->ifhdoc][0], STDIN_FILENO) < 0)
		ft_error(data, "  processfinal dup31", 1);
	if (dup2(data->outf, STDOUT_FILENO) < 0)
		ft_error(data, "  processfinal dup31", 1);
	close_fd(data->argc_copy, data);
	getcmd(data, argv[argc - 2]);
	if (!data->cmd[0])
		ft_error(data, "Command not found processfinal", 127);
	data->path = checkcmd(data->all_path, *data->cmd, data);
	if (!data->path)
		ft_error(data, "Command not found", 127);
	execve(data->path, data->cmd, data->envp_copy);
	ft_error(data, "execve1", 1);
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

void	init_variable(int argc, t_data *data)
{
	int	i;

	i = -1;
	while (argc > ++i)
		data->id[i] = 0;
	i = 0;
	data->pipefd = malloc(sizeof(int *) * (argc - 4 - data->ifhdoc + 1));
	if (data->pipefd == NULL)
		ft_error(data, "malloc", 1);
	while (argc - 4 - data->ifhdoc > i)
	{
		data->pipefd[i] = malloc(sizeof(int) * 2);
		if (data->pipefd[i] == NULL)
			ft_error(data, "malloc1", 1);
		data->pipefd[i][0] = 0;
		data->pipefd[i][1] = 0;
		i++;
	}
	data->pipefd[i] = NULL;
	i = -1;
	while (argc - 4 - data->ifhdoc > ++i)
	{
		if (pipe(data->pipefd[i]) < 0)
			ft_error(data, "pipe", 1);
	}
}
