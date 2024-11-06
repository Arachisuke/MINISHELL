/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:23:08 by ankammer          #+#    #+#             */
/*   Updated: 2024/11/06 14:04:48 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(t_my_env *my_env)
{
	while (my_env)
	{
		ft_printf_fd(1, "%s=%s\n", my_env->key, my_env->value);
		my_env = my_env->next;
	}
}
