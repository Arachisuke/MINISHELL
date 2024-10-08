/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:50:54 by wzeraig           #+#    #+#             */
/*   Updated: 2024/10/01 13:02:01 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*negative_hollow(char *s)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	j = 0;
	while (s[++i])
		if (s[i] < 0)
			j++;
	str = malloc(sizeof(char) * (i + 1 - j));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i])
		if (s[i] > 0) // a changer
			str[j++] = s[i]; 
	free(s);
	str[j] = '\0';
	return (str);
}
