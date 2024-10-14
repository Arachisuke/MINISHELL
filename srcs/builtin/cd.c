/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:22:47 by ankammer          #+#    #+#             */
/*   Updated: 2024/10/14 17:20:51 by wzeraig          ###   ########.fr       */
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
				return (ft_final(all, NULL, ERR_MALLOC));
		}
		else if (!ft_strncmp(my_env->key, "PWD", 3))
		{
			free(my_env->value);
			my_env->value = ft_strdup(pwd);
			if (!my_env->value)
				return (ft_final(all, NULL, ERR_MALLOC));
		}
		my_env = my_env->next;
	}
	free(oldpwd);
	free(pwd);
	return (SUCCESS);
}

void	exec_cd(char *path, t_all *all)
{
	int		i;
	char	*oldpwd;

	i = 0;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		ft_printf_fd(2, "cd: error retrieving current directory: %s\n",
			strerror(errno));
		free(path);
		ft_final(all, "error env", ERR_ENV);
	}
	if (chdir(path) == -1)
	{
		ft_printf_fd(2, "cd: %s: %s\n", path, strerror(errno));
		free(path);
		free(oldpwd);
		return ;
	}
	if (new_oldpwd(all->my_env, oldpwd, path, all))
	{
		free(path);
		free(oldpwd);
		ft_final(all, "error env", ERR_ENV);
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
				ft_final(all, NULL, ERR_MALLOC);
			return (home);
		}
		my_env = my_env->next;
	}
	ft_printf_fd(2, "cd: HOME not set\n");
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
		ft_printf_fd(2, "cd : %s: %s\n", path, strerror(errno));
		return (ERR_OPEN_DIR);
	}
	closedir(dir);
	return (SUCCESS);
}

void	ft_cd(t_simple_cmds *cmds, t_all *all)
{
	char	*pwd;

	if (cmds->strs[2])
	{
		ft_printf_fd(2, "cd: too many arguments\n");
		return ;
	}
	if (!cmds->strs[1])
		pwd = get_home(all->my_env, all);
	else
	{
		if (check_dir(cmds->strs[1], all))
		{
			ft_printf_fd(2, "cd: %s: %s", strerror(errno), cmds->strs[1]);
			return ;
		}
		pwd = ft_strdup(cmds->strs[1]);
	}
	if (!pwd)
	{
		ft_final(all, NULL, ERR_MALLOC);
		return ;
	}
	exec_cd(pwd, all);
}