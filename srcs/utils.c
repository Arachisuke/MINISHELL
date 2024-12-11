/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:35:24 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/10 12:33:39 by wzeraig          ###   ########.fr       */
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
int	ft_strictcmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (ft_strlen(s2) != ft_strlen(s1))
		return(1);

	while (n > i && s1[i] == s2[i] && s1[i])
		i++;
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}