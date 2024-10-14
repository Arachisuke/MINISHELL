/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:52:42 by ankammer          #+#    #+#             */
/*   Updated: 2024/10/14 16:26:27 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	fill_key_env(char **envp, int i, char **key)
{
	int	equal_sign;
	int	j;

	j = -1;
	equal_sign = 0;
	while (envp[i][++j] != '=')
		equal_sign++;
	j = -1;
	*key = malloc(sizeof(char) * (equal_sign + 1));
	if (!*key)
		return (ERR_MALLOC);
	while (++j < equal_sign)
		(*key)[j] = envp[i][j];
	(*key)[j] = '\0';
	return (SUCCESS);
}

int	fill_value_env(char **envp, int i, char **value)
{
	int	len_value;
	int	j;
	int	k;

	k = 0;
	j = -1;
	len_value = 0;
	while (envp[i][j] != '=')
		j++;
	k = j + 1;
	while (envp[i][k + len_value])
		len_value++;
	j = -1;
	*value = malloc(sizeof(char) * (len_value + 1));
	if (!*value)
		return (ERR_MALLOC);
	while (++j < len_value)
		(*value)[j] = envp[i][k + j];
	(*value)[j] = '\0';
	return (SUCCESS);
}

t_my_env	**ft_myenv(t_all *all, char **envp)
{
	int			i;
	t_my_env	*my_env;

	i = 0;
	while (envp[i])
	{
		create_node_env(&my_env, all, envp, i);
		i++;
	}
	i = 0;
	while (envp[i])
	{
		if (fill_key_env(envp, i, &my_env->key))
			return (ft_final(all, NULL, ERR_MALLOC));
		if (fill_value_env(envp, i, &my_env->value))
			return (ft_final(all, NULL, ERR_MALLOC));
		if (my_env->next)
			my_env = my_env->next;
		i++;
	}
	return (my_env);
}
