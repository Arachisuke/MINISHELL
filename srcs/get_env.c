/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:52:42 by ankammer          #+#    #+#             */
/*   Updated: 2024/09/25 15:46:17 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_env(char **env, t_all *all)
{
	if (!env)
		return (1);
	all->envp = env;
	if (!all->envp)
		return (1);
	return (0);
}
