/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:49:04 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/19 17:01:33 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free(char **strs)
{
	int i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i]) // ca seg ou pas
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return ;
}