/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:17:30 by wzeraig           #+#    #+#             */
/*   Updated: 2024/11/12 15:25:20 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_error(t_all *all, char *str, int msg)
{
	close_fd(data->argc_copy, data);
	if (data->ifhdoc)
		unlink(".heredoc_tmp");
	if (data->pipefd)
		ft_free2(data->pipefd);
	if (data->id)
		free(data->id);
	if (data->all_path)
		ft_free((void **)data->all_path);
	if (data->path)
		free(data->path);
	if (data->cmd)
		ft_free((void **)data->cmd);
	if (str)
		perror(str);
	return(msg);
}

void	close_fd(int argc, t_data *data)
{
	int	i;

	i = 0;
	if (data->heredoc)
		close(data->heredoc);
	if (data->infile > 0)
		close(data->infile);
	if (data->outf)
		close(data->outf);
	while ((argc - 4) - data->ifhdoc > i)
	{
		if (data->pipefd[i])
		{
			close(data->pipefd[i][0]);
			close(data->pipefd[i][1]);
		}
		i++;
	}
}

void	init_struct(t_pipex *pipex, t_simple_cmds *cmds, t_my_env *envp)
{
	int	i;

	i = -1;
	pipex->all_path = NULL; // c tout le path des commandes
	pipex->path = NULL;     // le path je le recupere dans checkcmd
	pipex->status = 0;
	pipex->nbrcmd = ft_lstsize(cmds);
	pipex->cmds = cmds;
	pipex->pid = malloc(sizeof(int) * (pipex->nbrcmd - 1)); // fois le nombre de node de cmds
	while (pipex->nbrcmd > ++i)
		pipex->pid[i] = 0;
	pipex->pipefd = malloc(sizeof(int *) * (pipex->nbrcmd - 1)); // fois le nombre de node de cmds -1
	if (pipex->pipefd == NULL)
		ft_error(pipex, "malloc", 1);
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

void	ft_free(void **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		if (strs[i])
			free(strs[i]);
		i++;
	}
	free(strs);
}
