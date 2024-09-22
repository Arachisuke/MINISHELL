/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:18:46 by ankammer          #+#    #+#             */
/*   Updated: 2024/09/21 15:43:07 by wzeraig          ###   ########.fr       */
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