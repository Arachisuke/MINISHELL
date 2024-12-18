/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:22:47 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/17 15:43:32 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_home(t_my_env *my_env, t_all *all)
{
	char	*home;

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
