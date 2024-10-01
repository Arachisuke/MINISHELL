/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:51:02 by wzeraig           #+#    #+#             */
/*   Updated: 2024/10/01 17:52:35 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	verif_quotes(t_all *all, char *line)
{
	int		i;
	char	quote;
	int		flag;

	quote = 0;
	flag = 0;
	i = -1;
	while (line[++i])
	{
		if ((line[i] == SQ || line[i] == DQ) && flag == 0) // debut quotes
		{
			quote = line[i];
			flag = 1;
		}
		else if (flag == 1 && line[i] == ' ')
			line[i] = line[i] * -1;
		else if (line[i] == quote && flag == 1) /// fin quotes
			flag = 0;
	}
	if (flag == 1)
		return (ft_final(all, "unclosed quotes" , ERR_SYNTAX));
	return (0);
}

int	verif_space(char *line) // elle sers a quoi ?
{
	int i;

	i = 0;
	if (!line)
		return (1);
	while (is_space(line[i]))
		i++;
	if ((size_t)i == ft_strlen(line))
		return (1);
	return (0);
}
