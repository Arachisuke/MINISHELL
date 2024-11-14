/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:25:08 by wzeraig           #+#    #+#             */
/*   Updated: 2024/11/14 15:20:44 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*checkcmd(t_all *all, char **all_path, char *cmd, t_pipex *pipex)
{
	int		i;
	char	*path;

	i = 0;
	if (ft_strchr(cmd, '.') && ft_strlen(cmd) == 1)
		return (path = ft_strdup(""), path);
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == -1)
			return (ft_errchild(all, "Permission denied", pipex, 126), NULL);
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

void	parsing_pipex(t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	// if (!ft_strncmp(data->argv_copy[1], "here_doc", 8))
	// 	here_doc(data, data->argv_copy);
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
void	ft_free2(int **tab, t_pipex *pipex)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (pipex->nbrcmd > i)
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
void	ft_free2child(int **tab, t_pipex *pipex)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (pipex->nbrcmd > i)
	{
		if (tab[i])
			tab[i] = NULL;
		i++;
	}
	tab = NULL;
}

int	wait_childs(pid_t pid, t_pipex *pipex)
{
	int	code;

	code = EXIT_FAILURE;
	while (errno != ECHILD)
		if (wait(&pipex->status) == pid && WIFEXITED(pipex->status))
			code = WEXITSTATUS(pipex->status);
	if (pid == -1)
		return (127);
	return (code);
}
int	envlist_envchar(t_pipex *pipex, t_my_env *envp)
{
	t_my_env	*tmp;
	int			i;

	i = 0;
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
int	ft_errchild(t_all *all, char *str, t_pipex *pipex, int msg)
{
	close_fd(pipex, all->cmds);
	if (pipex->pipefd)
		ft_free2(pipex->pipefd, pipex);
	if (pipex->pid)
		free(pipex->pid);
	if (pipex->all_path)
		ft_free((void **)pipex->all_path);
	if (pipex->path)
		free(pipex->path);
	if (pipex->env)
		free_strs(&pipex->env);
	if (str)
		perror(str);
	exit(msg);
}