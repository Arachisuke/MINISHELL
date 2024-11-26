/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:21:50 by ankammer          #+#    #+#             */
/*   Updated: 2024/11/26 11:34:49 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// void    haine_or_not(char **args, int *j, int *i, int **n)
// {
//     while (args[*j])
//     {
//         while (args[*j][(*i)++])
//         {
//             if (args[*j][*i] == 'n')
//             {
//                 while (args[*j][*i] == 'n')
//                     (*i)++;
//                 if (args[*j][*i] && args[*j][*i] != 'n') // cas -nnnnnoo
//                     break ;
//                 (*j)++;
//                 *i = 0;
//                 **n = 1;
//             }
//             else
//             {
//                 *i = 0;
//                 break ;
//             }
//         }
//         if (args[*j][*i] && args[*j][*i] != 'n') // cas -nnnnnoo
//             break ;
//         (*j)++;
//         **n = 1;
//     }
// }
void	haine_or_not(char **args, int *j, int *i, int **n)
{
	int a;
	int b;

	a = *j;
	b = *i;
	while (args[a])
	{
		b++; // je suis arrive au suppose n
		if (args[a] && args[a][b] != 'n')
		{
			while (args[a][b] == 'n')
				b++;
			if (args[a][b] && args[a][b] != 'n') // cas -nnnnnoo
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
	if (!n)
		write(1, "\n", 1);
	return (SUCCESS);
}