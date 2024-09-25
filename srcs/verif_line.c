/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:51:02 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/24 14:34:39 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	verif_quotes(char *line)
{
	int		i;
	char	quote;
	int		flag;

	i = 0;
	quote = 0;
	flag = 0;
	i = -1;
	while (line[++i])
	{
		if ((line[i] == SQ || line[i] == DQ) && flag == 0)
		{
			quote = line[i];
			flag = 1;
		}
		// else if (line[i] != quote && flag == 1)
		// line[i] *= -1;
		else if (line[i] == quote && flag == 1)
			flag = 0;
	}
	if (flag == 1)
		return (0);
	return (1);
}
int	verif_space(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (is_space(line[i]))
		i++;
	if ((size_t)i == ft_strlen(line))
		return (0);
	return (1);
}

int	all_verifs(char *line)
{
	int	ret;

	ret = 0;
	ret = verif_space(line);
	if (ret == 1)
		ret = verif_quotes(line);
	return (ret);
}
