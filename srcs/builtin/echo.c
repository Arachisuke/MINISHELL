/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:21:50 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/05 14:06:28 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	haine_or_not(char **args, int *j, int *i, int **n)
{
	int	a;
	int	b;

	a = *j;
	b = *i;
	while (args[a])
	{
		b++;
		if (args[a] && args[a][b] != 'n')
		{
			while (args[a][b] == 'n')
				b++;
			if (args[a][b] && args[a][b] != 'n')
				break ;
			a++;
			*j = a;
			**n = 1;
			b = 0;
		}
	}
}

int	check_n(char **args, int *n)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (args[j] && args[j][i] == '-')
		haine_or_not(args, &j, &i, &n);
	return (j);
}

int	ft_echo(char **args, t_all *all)
{
	int	n;
	int	i;

	n = 0;
	i = check_n(args, &n);
	if (n && !args[i])
		return (all->exit_code = 0, 0);
	if (!n && !args[i])
	{
		ft_putchar_fd('\n', 1);
		return (all->exit_code = 0, 0);
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i] && args[i][0] != '\0')
			write(1, " ", 1);
	}
	if (!n)
		write(1, "\n", 1);
	return (all->exit_code = 0, SUCCESS);
}
