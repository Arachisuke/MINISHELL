/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:23:51 by ankammer          #+#    #+#             */
/*   Updated: 2024/10/13 18:29:58 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_export(t_all *all, char **args)
{
	int i;
	int max;
	int newline;

	newline = 1;
	max = alloc_env(all->envp);
	all->envp = malloc(sizeof(char *) * (max + 1 + newline));
	i = 0;
	while (i <= max)
	{
		all->envp[i] = ft_strdup(all->envp);
		i++;
	}
	all->envp[i++] = 
	all->envp[i] = NULL;
	return (all->envp);
}