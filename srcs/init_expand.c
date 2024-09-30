/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:57:36 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/29 16:58:52 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_expand	*create_nodexpand(t_expand **expand, int nbrexpand)
{
	int	i;

	i = 0;
	while (i < nbrexpand)
	{
		ft_back_expand(expand, ft_new_expand());
		i++;
	}
	return (*expand);
}

t_expand	*ft_last_expand(t_expand *lst) // a modifier
{
	t_expand *actuel;

	if (!lst)
		return (NULL);
	actuel = lst;
	while (actuel->next)
		actuel = actuel->next;
	return (actuel);
}

t_expand	*ft_new_expand(void)
{
	t_expand	*elem;

	elem = malloc(sizeof(t_expand));
	if (!elem)
		return (NULL);
	elem->i = 0;
	elem->lenafter = 0;
	elem->lenbefore = 0;
	elem->is_file = 0;
	elem->next = NULL;
	elem->strexpanded = NULL;
	elem->strtoexpand = NULL;
	return (elem);
}

t_expand	*ft_back_expand(t_expand **lst, t_expand *new)
{
	t_expand	*last;

	if (!new)
		return (NULL);
	if (!*lst)
		*lst = new;
	else
	{
		last = ft_last_expand(*lst);
		last->next = new;
	}
	return(new);
}
