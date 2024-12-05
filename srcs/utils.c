/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:35:24 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/05 12:10:01 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	fill_tab(int indice, int *tab, int **k)
{
	tab[**k] = indice;
	(**k)++;
}

int	checktab(int *tab, int j)
{
	int	i;

	i = 0;
	while (tab[i] >= 0)
	{
		if (tab[i] == j)
			return (1);
		i++;
	}
	return (0);
}

int	count_arg(t_lexer *curr)
{
	t_lexer	*tmp;
	int		count;

	count = 0;
	tmp = curr;
	if (tmp->token == STRING && !tmp->prev)
		count = 1;
	if (tmp->token == PIPE && tmp->next)
		tmp = tmp->next;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->token == STRING && tmp->prev && (tmp->prev->token == STRING
				|| tmp->prev->token == PIPE))
			count++;
		tmp = tmp->next;
	}
	return (count);
}
