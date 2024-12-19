/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:32:04 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/17 19:33:21 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	init_shlvl(t_all *all, t_my_env *my_env)
{
	int		shlvl;
	char	*shlvl_str;

	shlvl = ft_atoi(my_env->value);
	shlvl++;
	shlvl_str = ft_itoa(shlvl);
	if (!shlvl_str)
		return (ft_final(all, NULL, NULL, 1));
	free(my_env->value);
	my_env->value = shlvl_str;
	return (SUCCESS);
}
