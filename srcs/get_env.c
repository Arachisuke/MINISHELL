/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:52:42 by ankammer          #+#    #+#             */
/*   Updated: 2024/09/25 12:27:08 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_env(char **env, t_all *all)
{
	int	i;

	if (!env)
		return (1);
	i = 0;
	while (env[i])
		i++;
	all->expand->envp = malloc(sizeof(char *) * (i + 1));
	if (!all->expand->envp)
		return (1);
	i = -1;
	while (env[++i])
		all->expand->envp[i] = ft_strdup(env[i]);
	if (all->expand->envp)
		return (ft_free(all->expand->envp), 1);
	return (0);
}
