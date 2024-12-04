/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:52:42 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/03 15:58:17 by ankammer         ###   ########.fr       */
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
		return (1);
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
		return (1);
	while (++j < len_value)
		(*value)[j] = envp[i][k + j];
	(*value)[j] = '\0';
	return (SUCCESS);
}

t_my_env	*minimal_env(void)
{
	t_my_env	*my_env;
	t_my_env	*my_env_tmp;
	int			shlvl;
	int			i;

	i = -1;
	shlvl = 0;
	while (++i < 3)
		create_node_env(&my_env, i);
	my_env_tmp = my_env;
	my_env_tmp->key = ft_strdup("PWD");
	my_env_tmp->value = getcwd(NULL, 0);
	my_env_tmp = my_env_tmp->next;
	my_env_tmp->key = ft_strdup("SHLVL");
	my_env_tmp->value = ft_itoa(++shlvl);
	my_env_tmp = my_env_tmp->next;
	my_env_tmp->key = ft_strdup("_");
	my_env_tmp->value = ft_strdup("/usr/bin/env");
	return (my_env);
}

t_my_env	*ft_myenv(t_all *all, char **envp)
{
	int			i;
	t_my_env	*my_env;
	t_my_env	*my_env_tmp;

	i = 0;
	if (!envp)
		return (minimal_env());
	// return (NULL);
	while (envp[i])
	{
		create_node_env(&my_env, i);
		i++;
	}
	my_env_tmp = my_env;
	i = 0;
	while (envp[i])
	{
		if (fill_key_env(envp, i, &my_env->key))
			return (ft_final(all, NULL, NULL, 1), NULL);
		if (fill_value_env(envp, i, &my_env->value), NULL)
			return (ft_final(all, NULL, NULL, 1), NULL);
		if (my_env->next)
			my_env = my_env->next;
		i++;
	}
	return (my_env_tmp);
}
