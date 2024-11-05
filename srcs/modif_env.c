/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:57:23 by wzeraig           #+#    #+#             */
/*   Updated: 2024/11/05 15:19:08 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	replace_node_content(t_my_env *env, char *key, char *value)
{
	free(env->key);
	free(env->value);
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
}

void	add_node(t_my_env *env, char *key, char *value, int index)
{
	t_my_env	*tmp_env;
	int			i;

	i = 0;
	create_node_env(&env, index);
	tmp_env = ft_last_env(env);
	tmp_env->index = index;
	tmp_env->key = ft_strdup(key);
	tmp_env->value = ft_strdup(value);
}

t_my_env	*modify_env(char *key, char *value, t_my_env *env)
{
	t_my_env *tmp_env;
	int index;

	index = 0;
	tmp_env = env;
	while (tmp_env)
	{
		if (ft_strlen(tmp_env->key) == ft_strlen(key))
			if (!ft_strncmp(tmp_env->key, key, ft_strlen(tmp_env->key)))
				replace_node_content(tmp_env, key, value);
		tmp_env = tmp_env->next;
		index++;
	}
	if (!tmp_env)
		add_node(env, key, value, index);
	return (env);
}