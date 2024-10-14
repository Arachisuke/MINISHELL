/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:52:42 by ankammer          #+#    #+#             */
/*   Updated: 2024/10/14 13:29:13 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	fill_key_env(char **envp, int i, char *key)
{
	int	equal_sign;
	int	j;

	j = -1;
	equal_sign = 0;
	while (envp[i][++j] != '=')
		equal_sign++;
	j = -1;
	key = malloc(sizeof(char) * (equal_sign + 1));
	if (!key)
		return (ERR_MALLOC);
	while (envp[i][++j] != '=')
		key[j] = envp[i][j];
	key[j] = '\0';
	return (SUCCESS);
}

char	*fill_value_env(char **envp, int i, char *value)
{
	int	len_value;
	int	j;
	int k;

	k = 0;
	j = -1;
	len_value = 0;
	while (envp[i][j] != '=')
		j++;
	k = j;
	while (envp[i][k])
	{
		len_value++;
		k++;
	}
	j = -1;
	value = malloc(sizeof(char) * (len_value + 1));
	if (!value)
		return (ERR_MALLOC);
	while (envp[i][k])
		value[++j] = envp[i][k++];
	value[j] = '\0';
	return (SUCCESS);
}

char	**ft_myenv(t_all *all, char **envp, t_my_env *my_env)
{
	int			i;
	t_my_env	*tmp;

	tmp = my_env;
	i = 0;
	while (envp[i])
	{
		create_node_env(&tmp, all, envp, i);
		i++;
	}
	tmp = my_env;
	i = 0;
	while (envp[i])
	{
		if (fill_key_env(envp, i, tmp->key))
			return (ft_final(all, NULL, ERR_MALLOC));
		if (fill_value_env(envp, i, tmp->value))
			return (ft_final(all, NULL, ERR_MALLOC));
		if (tmp->next)
			tmp = tmp->next;
		i++;
	}
}
