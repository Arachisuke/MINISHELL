/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:25:08 by wzeraig           #+#    #+#             */
/*   Updated: 2024/11/11 15:30:36 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*checkcmd(char **all_path, char *cmd, t_data *data)
{
	int		i;
	char	*path;

	i = 0;
	if (ft_strchr(cmd, '.') && ft_strlen(cmd) == 1)
		return (path = ft_strdup(""), path);
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == -1)
			ft_error(data, "Permission denied", 126);
		return (cmd);
	}
	if (!all_path)
		return (NULL);
	while (all_path[i])
	{
		path = ft_strjoin(all_path[i], "/");
		path = strjoinfree(path, cmd);
		if (access(path, F_OK) == 0)
			return (path);
		if (path)
			free(path);
		i++;
	}
	return (NULL);
}

void	parsing(int argc, char **envp, t_data *data)
{
	int	i;

	if (argc < 5)
		ft_error(data, "arguments", 1);
	i = 0;
	if (!ft_strncmp(data->argv_copy[1], "here_doc", 8))
		here_doc(data, data->argv_copy);
	if (!envp)
		return ;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			data->all_path = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
}

void	ft_free2(int **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
}

int	wait_childs(pid_t pid, t_data *data)
{
	int	code;

	code = EXIT_FAILURE;
	while (errno != ECHILD)
		if (wait(&data->status) == pid && WIFEXITED(data->status))
			code = WEXITSTATUS(data->status);
	if (pid == -1)
		return (127);
	return (code);
}

void	getcmd(t_data *data, char *cmd)
{
	char	*str;
	int		i;

	i = -1;
	if (strchr(cmd, '\''))
	{
		str = ft_strdup(" ");
		data->cmd = ft_split(cmd, '\'');
		while (data->cmd[++i])
			str = strjoinfree(str, data->cmd[i]);
		free(data->cmd);
		data->cmd = ft_split(str, ' ');
		free(str);
	}
	else
		data->cmd = ft_split(cmd, ' ');
}
