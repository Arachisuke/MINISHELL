/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:23:08 by ankammer          #+#    #+#             */
/*   Updated: 2024/11/11 15:15:24 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(t_my_env *my_env)
{
	while (my_env)
	{
		ft_printf_fd(1, "%s=%s\n", my_env->key, my_env->value);
		my_env = my_env->next;
	}
}
char	*free_env(t_my_env **env) // 3 ou 1
{
	t_my_env *tmp;

	if (!*env || !env)
		return (NULL);
	tmp = *env;
	while (*env)
	{
		if ((*env)->key)
			free((*env)->key);
		if ((*env)->value)
			free((*env)->value);
		tmp = tmp->next;
		free(env);
		*env = NULL;
		*env = tmp;
	}
	return (NULL);
}