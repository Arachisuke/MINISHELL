/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:53:17 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/26 15:27:38 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	find_var(t_all *all, char **envp)
{
	int i;
	t_expand *tmp;

	i = 0;
	tmp = all->expand;
	while (tmp)
	{
		while (envp[i])
		{
			if ((!ft_strncmp(envp[i], tmp->strtoexpand, tmp->lenbefore - 1))
				&& (envp[i][tmp->lenbefore - 1] == '='))
			{
				tmp->strexpanded = envp[i] + tmp->lenbefore;
				break ;
			}
			i++;
		}
		if (tmp->strexpanded)
			tmp->lenafter = ft_strlen(tmp->strexpanded);
		tmp = tmp->next;
		i = 0;
	}
	return (0);
	// chercher dans all.envp la strtoexpand.
}