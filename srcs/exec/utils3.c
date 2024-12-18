/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:47:34 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/17 15:50:19 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	envlist_envchar(t_pipex *pipex, t_my_env *envp)
{
	t_my_env	*tmp;
	int			i;

	i = 0;
	if (!envp)
		return (0);
	tmp = envp;
	pipex->env = malloc(sizeof(char *) * (ft_lstsize_env(envp) + 1));
	if (!pipex->env)
		return (1);
	while (tmp)
	{
		pipex->env[i] = strjoinegal(tmp->key, tmp->value);
		tmp = tmp->next;
		i++;
	}
	pipex->env[i] = NULL;
	return (0);
}

char	*strjoinegal(char const *s1, char const *s2)
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
	s = malloc((sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 2));
	if (s == NULL)
		return (NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i++] = '=';
	while (s2[j])
		s[i++] = s2[j++];
	s[i] = '\0';
	return (s);
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
