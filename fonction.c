/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:38:51 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/16 18:44:54 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

char	**malloc_input(char *line)
{
	int count;
	char **strs;
	int i;

	i = 0;

	count = count_word(line);
	while (line[i])
	{
		if (is_token(line[i]))
			count++;
		i++;
	}
	strs = malloc(sizeof(char *) * count + 1); // rajoute + 1
	strs[count] = NULL;
	//printf("strs[count] = %s", strs[count]);
	if (!strs) // fonction ?
		return(NULL);
	return (strs);
}