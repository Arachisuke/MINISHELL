/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandornot_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:35:30 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/17 18:37:59 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_underscore(char *str, int i)
{
	if (str[i] == '$' && str[i + 1] && str[i + 1] == '_')
	{
		while (str[i + 1] && str[i + 1] != ' ')
		{
			str[i++] = ' ';
			str[i] = ' ';
		}
		return (1);
	}
	return (0);
}

int	condition(char *str, int i, int flag)
{
	if (checkredir(str, i))
		return (1);
	if (!flag && str[i] == '$' && str[i + 1] && str[i + 1] == SQ)
		return (str[i] = -87, 1);
	if (!flag && str[i] == '$' && str[i + 1] && str[i + 1] == DQ)
		return (str[i] = -87, 1);
	if (str[i] == '$' && str[i + 1] && ft_isdigit(str[i + 1]))
		return (str[i] = ' ', str[i + 1] = ' ', 1);
	else if (is_underscore(str, i))
		return (1);
	else if (str[i] == '$' && str[i + 1] && str[i + 1] == SQ)
		return (1);
	else if (str[i] == '$' && str[i + 1] && str[i + 1] == DQ)
		return (1);
	else if (str[i] == '$' && str[i + 1] && str[i + 1] == '$')
		return (SUCCESS);
	else if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
		return (SUCCESS);
	else if (str[i] == '$' && str[i + 1] && !ft_isalpha(str[i + 1]))
		return (1);
	else if (str[i] == '$' && str[i + 1])
		return (SUCCESS);
	return (1);
}
