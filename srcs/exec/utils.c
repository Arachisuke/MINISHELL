/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macos <macos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:17:30 by wzeraig           #+#    #+#             */
/*   Updated: 2024/12/15 16:32:09 by macos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_fd_pid(int ***pipefd, int **pid, t_pipex *pipex)
{
	if (*pipefd)
	{
		free_tab(*pipefd, pipex);
		*pipefd = NULL;
	}
	if (*pid)
	{
		free(*pid);
		*pid = NULL;
	}
}

int	ft_errparent(t_all *all, char *str, t_pipex *pipex, int msg)
{
	close_fd(pipex, all->cmds);	
	free_fd_pid(&pipex->pipefd, &pipex->pid, pipex);
	if (pipex->all_path)
	{
		free_strs(pipex->all_path);
		pipex->all_path = NULL;
	}
	if (pipex->path)
		pipex->path = NULL;
	if (pipex->env)
	{
		free_strs(pipex->env);
		pipex->env = NULL;
	}
	if (str)
		ft_printf_fd(2, "minishell: %s: %s\n", pipex->cmds->strs[0], str);
	pipex->cmds = NULL;
	return (msg);
}

int	ft_errchild(t_all *all, char *str, t_pipex *pipex, int msg)
{
	if (str)
		ft_printf_fd(2, "minishell: %s: %s\n", pipex->cmds->strs[0], str);
	close_fd(pipex, all->cmds);
	ft_final(all, NULL, NULL, 0);
	free_env(&all->my_env);
	free_fd_pid(&pipex->pipefd, &pipex->pid, pipex);
	if (pipex->all_path)
	{
		free_strs(pipex->all_path);
		pipex->all_path = NULL;
	}
	if (pipex->path)
	{
		free(pipex->path);
		pipex->path = NULL;
	}
	if (pipex->env)
	{
		free_strs(pipex->env);
		pipex->env = NULL;
	}
	pipex->cmds = NULL;
	exit(msg);
}

void	close_fd(t_pipex *pipex, t_simple_cmds *cmds)
{
	int	i;

	i = 0;
	if (cmds && cmds->redir && cmds->redir->fd_here_doc)
		close(cmds->redir->fd_here_doc);
	if (cmds && cmds->fd_infile)
		close(cmds->fd_infile);
	if (cmds && cmds->fd_outfile > 0)
		close(cmds->fd_outfile);
	while (pipex->nbrcmd - 1 > i)
	{
		if (pipex->pipefd[i])
		{
			close(pipex->pipefd[i][0]);
			close(pipex->pipefd[i][1]);
		}
		i++;
	}
}

int	init_struct(t_all *all, t_pipex *pipex, t_simple_cmds *cmds)
{
	int	i;

	i = -1;
	pipex->all_path = NULL;
	pipex->path = NULL;
	pipex->status = 0;
	pipex->nbrcmd = ft_size_cmds(cmds);
	pipex->pipefd = NULL;
	pipex->cmds = cmds;
	pipex->last_outfile = NULL;
	pipex->last_infile = NULL;
	pipex->env = NULL;
	pipex->pid = malloc(sizeof(pid_t) * pipex->nbrcmd);
	while (pipex->nbrcmd > ++i)
		pipex->pid[i] = 0;
	if (pipex->nbrcmd > 1)
		pipex->pipefd = malloc(sizeof(int *) * (pipex->nbrcmd - 1));
	if (pipex->pipefd == NULL && pipex->nbrcmd > 1)
		return (ft_errchild(all, "malloc", pipex, 1));
	return (0);
}

char	*strjoinfree(char const *s1, char const *s2)
{
	char	*s;
	int		i;
	int		j;

	if (s1 == NULL)
		return (NULL);
	if (s2 == NULL)
		return (NULL);
	j = 0;
	i = 0;
	s = malloc((sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1));
	if (s == NULL)
		return (NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	while (s2[j])
		s[i++] = s2[j++];
	s[i] = '\0';
	free((char *)s1);
	return (s);
}
