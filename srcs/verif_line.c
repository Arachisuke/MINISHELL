/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:51:02 by wzeraig           #+#    #+#             */
/*   Updated: 2024/10/03 15:39:39 by wzeraig          ###   ########.fr       */
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
		return (ft_final(all, "unclosed quotes", ERR_SYNTAX));
	return (SUCCESS);
}

int	firstquotecheck(char *line)
{
	if (line[0] < 0 && line[1] && line[1] < 0 && line[2] && ft_isalpha(line[2]))
		return (1);
	if (line[0] < 0 && line[1] && line[1] < 0 && line[2] && ft_isalpha(line[2]))
		return (1);
	return (-1);
}
int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	return (i);
}

int	verif_space(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!is_space(str[i]))
			return (1);
		i++;
	}
	return (0);
}