/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:23:08 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/05 14:07:28 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(t_my_env *my_env, t_all *all)
{
	if (!my_env)
		return ;
	if (all->cmds->strs[0] && all->cmds->strs[1])
	{
		if (all->cmds->strs[1][0] == '-' && all->cmds->strs[1][1]
			&& ft_isalpha(all->cmds->strs[1][1]))
		{
			ft_printf_fd(2, "env: invalid option -- '%c'\n",
				all->cmds->strs[1][0]);
			all->exit_code = 125;
		}
		else
		{
			ft_printf_fd(2, "env: %s: No such file or directory\n",
				all->cmds->strs[1]);
			all->exit_code = 127;
		}
		return ;
	}
	while (my_env)
	{
		ft_printf_fd(1, "%s=%s\n", my_env->key, my_env->value);
		my_env = my_env->next;
	}
}

char	*free_env(t_my_env **env)
{
	t_my_env	*tmp;

	if (!*env || !env)
		return (NULL);
	tmp = *env;
	while (*env)
	{
		if ((*env)->key)
		{
			free((*env)->key);
			(*env)->key = NULL;
		}
		if ((*env)->value)
		{
			free((*env)->value);
			(*env)->value = NULL;
		}
		tmp = tmp->next;
		free(*env);
		*env = NULL;
		*env = tmp;
	}
	return (NULL);
}
