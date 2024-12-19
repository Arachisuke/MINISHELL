/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:52:42 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/17 19:32:24 by ankammer         ###   ########.fr       */
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

int	set_last_key(t_my_env *my_env_tmp)
{
	my_env_tmp->key = ft_strdup("_");
	if (!my_env_tmp->key)
		return (1);
	my_env_tmp->value = ft_strdup("/usr/bin/env");
	if (!my_env_tmp->value)
		return (1);
	return (0);
}

t_my_env	*minimal_env(t_all *all)
{
	t_my_env	*my_env;
	t_my_env	*my_env_tmp;
	int			i;

	i = -1;
	while (++i < 3)
		create_node_env(&my_env, i);
	my_env_tmp = my_env;
	my_env_tmp->key = ft_strdup("PWD");
	if (!my_env_tmp->key)
		return (ft_final(all, NULL, NULL, 1), NULL);
	my_env_tmp->value = getcwd(NULL, 0);
	if (!my_env_tmp->value)
		return (ft_final(all, NULL, NULL, 1), NULL);
	my_env_tmp = my_env_tmp->next;
	my_env_tmp->key = ft_strdup("SHLVL");
	if (!my_env_tmp->key)
		return (ft_final(all, NULL, NULL, 1), NULL);
	my_env_tmp->value = ft_strdup("1");
	if (!my_env_tmp->value)
		return (ft_final(all, NULL, NULL, 1), NULL);
	my_env_tmp = my_env_tmp->next;
	if (set_last_key(my_env_tmp))
		return (ft_final(all, NULL, NULL, 1), NULL);
	return (my_env);
}

void	set_node_env(t_my_env **my_env, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		create_node_env(my_env, i);
		i++;
	}
}

t_my_env	*ft_myenv(t_all *all, char **envp)
{
	int			i;
	t_my_env	*my_env;
	t_my_env	*my_env_tmp;

	i = 0;
	if (!envp || !*envp)
		return (minimal_env(all));
	set_node_env(&my_env, envp);
	my_env_tmp = my_env;
	i = -1;
	while (envp[++i])
	{
		if (fill_key_env(envp, i, &my_env->key))
			return (ft_final(all, NULL, NULL, 1), NULL);
		if (fill_value_env(envp, i, &my_env->value), NULL)
			return (ft_final(all, NULL, NULL, 1), NULL);
		if (ft_strncmp(my_env->key, "SHLVL", 5) == 0
			&& ft_strlen(my_env->key) == 5)
			init_shlvl(all, my_env);
		if (my_env->next)
			my_env = my_env->next;
	}
	return (my_env_tmp);
}
