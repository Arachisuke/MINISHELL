/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:24:05 by ankammer          #+#    #+#             */
/*   Updated: 2024/11/05 16:23:12 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*remove_env(t_my_env **env, int index)
{
	t_my_env	*env_tmp;
	t_my_env	*new_next;
	int			i;

	i = 0;
	if (!*env || !env)
		return (NULL);
	env_tmp = *env;
	while (i < index - 1)
	{
		env_tmp = env_tmp->next;
		i++;
	}
	new_next = env_tmp->next->next;
	free(env_tmp->next->key);
	free(env_tmp->next->value);
	free(env_tmp->next);
	env_tmp->next = new_next;
	while (env_tmp)
	{
		printf("")
		env_tmp->index--;
		env_tmp = env_tmp->next;
	}
	return (NULL);
}

t_my_env	*check_env(char *key, t_my_env *env)
{
	t_my_env	*tmp_env;
	int			index;

	index = 0;
	tmp_env = env;
	while (tmp_env)
	{
		if (ft_strlen(tmp_env->key) == ft_strlen(key))
			if (!ft_strncmp(tmp_env->key, key, ft_strlen(tmp_env->key)))
				remove_env(&env, index);
		tmp_env = tmp_env->next;
		index++;
	}
	return (env);
}

int	if_unset(t_all *all, char *line)
{
	int		i;
	int		flag;
	char	quotes;

	i = 0;
	quotes = 0;
	while (line[i])
	{
		if ((line[i] == -39 || line[i] == -34) && !flag)
		{
			flag = 1;
			quotes = line[i];
		}
		if (ft_strncmp(line + i, "unset", 5)) // exporta=ok
		{
			if (line[i + 4] && !flag)
				return (msg_error(all, ERR_EXPORT, line), 1);
			// modifier pour unset
			return (0);
		}
		if (line[i] == quotes && flag)
			flag = 0;
		i++;
	}
	return (1);
}

void	ft_unset(t_all *all, char **strs)
{
	int i;
	int j;

	i = 0;
	j = 1;

	int error;
	error = if_unset(all, strs[0]); // verification de la cmd unset
	if (error)
		return ;
	while (strs[j])
	{
		check_env(strs[j], all->my_env);
		j++;
	}
	ft_env(all->my_env);
	return ;
}