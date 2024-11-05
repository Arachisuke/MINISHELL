/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:21:50 by ankammer          #+#    #+#             */
/*   Updated: 2024/11/05 16:15:18 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_n(char **args, int *n)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (args[j])
	{
		while (args[j][i])
		{
			if (args[j][i++] == '-' && args[j][i] == 'n')
			{
				while (args[j][i] == 'n')
					i++;
				if (args[j][i] && args[j][i] != 'n') // cas -nnnnnoo
					break ;
			}
			else
				break ;
			j++;
		}
	}
	if (j > 0) // dnc ya un -n au debut de correction sans fioriture donc n = 1
		*n = 1;
	return (j); // et je renvoie le J qui rempli pas les conditions
}

int	ft_echo(char **args)
{
	int n;
	int i;

	n = 0;
	i = check_n(args, &n);
	if (n && !args[i])
		return (1);
	if (!n && !args[i])
	{
		ft_putchar_fd('\n', 1);
		return (1);
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i] && args[i][0] != '\0')
			write(1, " ", 1);
	}
	if (n)
		write(1, "\n", 1);
	return (SUCCESS);
}