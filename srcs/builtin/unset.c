/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:24:05 by ankammer          #+#    #+#             */
/*   Updated: 2024/11/07 11:50:45 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_my_env	*remove_the_first(t_my_env **env)
{
	t_my_env	*env_tmp;

	env_tmp = (*env)->next; // egal a la deuxieme node
	free((*env)->key);
	free((*env)->value);
	free(*env);
	*env = env_tmp;
	return (*env);
}

t_my_env	*remove_env(t_my_env **env, int index)
{
	t_my_env	*env_tmp;
	t_my_env	*new_next;
	int			i;

	i = -1;
	if (!*env || !env)
		return (NULL);
	env_tmp = *env;
	while (++i < index - 1)
		env_tmp = env_tmp->next;
	if (index == 0)
		return (remove_the_first(env));
	new_next = env_tmp->next->next;
	free(env_tmp->next->key);
	free(env_tmp->next->value);
	free(env_tmp->next);
	env_tmp->next = new_next;
	env_tmp = env_tmp->next;
	while (env_tmp)
	{
		env_tmp->index--;
		env_tmp = env_tmp->next;
	}
	return (*env);
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
				return (remove_env(&env, index));
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
		all->my_env = check_env(strs[j], all->my_env);
		j++;
	}
	return ;
}