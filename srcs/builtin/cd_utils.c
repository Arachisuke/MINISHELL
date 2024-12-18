/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:38:02 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/17 15:43:25 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	set_old_and_new_pwd(t_my_env **my_env, char *oldpwd, char *pwd)
{
	if (!ft_strncmp((*my_env)->key, "OLDPWD", 6))
	{
		if (oldpwd)
		{
			free((*my_env)->value);
			(*my_env)->value = ft_strdup(oldpwd);
			if (!(*my_env)->value)
				return (1);
		}
	}
	else if (!ft_strncmp((*my_env)->key, "PWD", 6))
	{
		if (pwd)
		{
			free((*my_env)->value);
			(*my_env)->value = ft_strdup(pwd);
			if (!(*my_env)->value)
				return (1);
		}
	}
	return (SUCCESS);
}

int	new_oldpwd(t_my_env *my_env, char *oldpwd, char *pwd, t_all *all)
{
	while (my_env)
	{
		if (set_old_and_new_pwd(&my_env, oldpwd, pwd))
			return (ft_final(all, NULL, NULL, 1));
		my_env = my_env->next;
	}
	if (oldpwd)
		free(oldpwd);
	if (pwd)
		free(pwd);
	return (SUCCESS);
}

char	*get_oldpwd(t_my_env *my_env, t_all *all)
{
	char	*oldpwd;

	oldpwd = NULL;
	while (my_env)
	{
		if (!ft_strncmp(my_env->key, "PWD", 3))
		{
			oldpwd = ft_strdup(my_env->value);
			if (!oldpwd)
				ft_final(all, NULL, NULL, 1);
			return (oldpwd);
		}
		my_env = my_env->next;
	}
	return (NULL);
}

void	exec_cd(char *path, t_all *all)
{
	char	*oldpwd;

	oldpwd = get_oldpwd(all->my_env, all);
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
