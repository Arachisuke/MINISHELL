/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:22:47 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/05 13:59:35 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	new_oldpwd(t_my_env *my_env, char *oldpwd, char *pwd, t_all *all)
{
	while (my_env)
	{
		if (!ft_strncmp(my_env->key, "OLDPWD", 6))
		{
			free(my_env->value);
			my_env->value = ft_strdup(oldpwd);
			if (!my_env->value)
				return (ft_final(all, NULL, NULL, 1));
		}
		else if (!ft_strncmp(my_env->key, "PWD", 3))
		{
			free(my_env->value);
			my_env->value = ft_strdup(pwd);
			if (!my_env->value)
				return (ft_final(all, NULL, NULL, 1));
		}
		my_env = my_env->next;
	}
	free(oldpwd);
	free(pwd);
	return (SUCCESS);
}

void	err_pwd(t_all *all, char **path)
{
	ft_printf_fd(2, "minishell: cd: %s: %s\n", *path, strerror(errno));
	free(*path);
	ft_final(all, NULL, ERR_ENV, 1);
}

void	exec_cd(char *path, t_all *all)
{
	int		i;
	char	*oldpwd;

	i = 0;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		err_pwd(all, &path);
	if (chdir(path) == -1)
	{
		ft_printf_fd(2, "minishell: cd: %s: %s\n", path, strerror(errno));
		return (free(path), free(oldpwd));
	}
	else
	{
		free(path);
		path = getcwd(NULL, 0);
	}
	if (new_oldpwd(all->my_env, oldpwd, path, all))
	{
		free(path);
		free(oldpwd);
		ft_final(all, "error env", ERR_ENV, 1);
	}
}

char	*get_home(t_my_env *my_env, t_all *all)
{
	int		i;
	char	*home;

	i = 0;
	home = NULL;
	while (my_env)
	{
		if (!ft_strncmp(my_env->key, "HOME", 4))
		{
			home = ft_strdup(my_env->value);
			if (!home)
				ft_final(all, NULL, NULL, 1);
			return (home);
		}
		my_env = my_env->next;
	}
	ft_printf_fd(2, "minishell: cd: HOME not set\n");
	return (NULL);
}

int	check_dir(char *path, t_all *all)
{
	DIR	*dir;

	if (!path)
		return (SUCCESS);
	dir = opendir(path);
	if (!dir)
	{
		ft_printf_fd(2, "minishell: cd : %s: %s\n", path, strerror(errno));
		all->exit_code = 1;
		return (1);
	}
	closedir(dir);
	return (SUCCESS);
}

int	count_line(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		i++;
	}
	return (i);
}

void	ft_cd(t_simple_cmds *cmds, t_all *all)
{
	char	*pwd;

	all->exit_code = 0;
	if (cmds && count_line(cmds->strs) > 2)
	{
		ft_printf_fd(2, "minishell: cd: too many arguments\n");
		all->exit_code = 1;
		return ;
	}
	if (!cmds->strs[1])
		pwd = get_home(all->my_env, all);
	else
	{
		if (check_dir(cmds->strs[1], all))
			return ;
		pwd = ft_strdup(cmds->strs[1]);
	}
	if (!pwd)
	{
		ft_final(all, NULL, NULL, 1);
		return ;
	}
	exec_cd(pwd, all);
}
