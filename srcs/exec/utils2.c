/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:25:08 by wzeraig           #+#    #+#             */
/*   Updated: 2024/12/17 15:49:49 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*checkcmd(t_all *all, char **all_path, char *cmd, t_pipex *pipex)
{
	int		i;
	char	*path;

	i = 0;
	if (cmd && access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == -1)
			return (ft_errchild(all, "Permission denied", pipex, 126), NULL);
		return (ft_strdup(cmd));
	}
	if (!all_path)
		return (NULL);
	while (all_path[i] && cmd)
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

void	parsing_pipex(t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			pipex->all_path = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
}

void	free_tab(int **tab, t_pipex *pipex)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (pipex->nbrcmd - 1 > i)
	{
		if (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
		}
		i++;
	}
	free(tab);
	tab = NULL;
}

int	wait_childs(pid_t pid, t_pipex *pipex, t_all *all)
{
	int	code;

	ft_nosignals();
	ft_signals_child();
	code = EXIT_FAILURE;
	while (errno != ECHILD)
	{
		if (wait(&pipex->status) == pid)
			if (WIFEXITED(pipex->status))
				code = WEXITSTATUS(pipex->status);
	}
	if (pid == -1)
		return (all->exit_code = 127, 127);
	all->exit_code = code;
	return (code);
}
