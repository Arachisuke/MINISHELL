/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:25:08 by wzeraig           #+#    #+#             */
/*   Updated: 2024/12/17 11:29:59 by wzeraig          ###   ########.fr       */
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

	 
	code = EXIT_FAILURE;
	while (errno != ECHILD)
		if (wait(&pipex->status) == pid && WIFEXITED(pipex->status))
			code = WEXITSTATUS(pipex->status);
	if (pid == -1)
		return (all->exit_code = 127, 127);
	all->exit_code = code;
	return (code);
}

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
