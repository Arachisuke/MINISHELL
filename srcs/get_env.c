/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:52:42 by ankammer          #+#    #+#             */
/*   Updated: 2024/09/25 14:45:25 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**get_env(char **envp, t_all *all)
{
	int	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
		i++;
	all->envp = malloc(sizeof(char *) * (i + 1));
	if (!all->envp)
		return (NULL);
	i = -1;
	while (envp[++i])
		all->envp[i] = ft_strdup(envp[i]);
	if (all->envp)
		return (ft_free(all->envp), NULL);
	return (all->envp);
}
