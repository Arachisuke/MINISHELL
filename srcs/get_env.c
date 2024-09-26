/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:52:42 by ankammer          #+#    #+#             */
/*   Updated: 2024/09/26 11:45:00 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**get_env(char **envp, t_all *all)
{
	if (!envp)
		return (NULL);
	all->envp = envp;
	if (!all->envp)
		return (NULL);
	return (0);
}
