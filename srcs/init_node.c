/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:36:08 by wzeraig           #+#    #+#             */
/*   Updated: 2024/10/03 11:42:40 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_lexer	*create_node(t_all *all, t_lexer **lexer, char ***strs)
{
	int	i;

	i = 0;
	while ((*strs)[i])
	{
		if (i == 0)
			*lexer = ft_new(all, (*strs)[i], i);
		else
			ft_back(lexer, ft_new(all, (*strs)[i], i));
		i++;
		if (!*lexer)
			return (NULL);
	}
	i = -1;
	return (*lexer);
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
t_lexer	*ft_new(t_all *all, void *content, int i)
{
	t_lexer	*elem;

	elem = malloc(sizeof(t_lexer));
	if (!elem)
		return (NULL);
	elem->string = content;
	elem->next = NULL;
	elem->prev = NULL;
	elem->i = i;
	if (checktab(all->tab, i))
		elem->token = STRING;
	else if (init_token(elem, all))
		return (NULL);
	return (elem);
}
void	ft_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*last;

	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		if (ft_size(*lst) == 1)
		{
			last = ft_last(*lst);
			last->next = new;
			new->next = NULL;
			new->prev = last;
		}
		else
		{
			last = ft_last(*lst);
			new->prev = last->next;
			last->next->next = new;
		}
	}
}

t_lexer	*ft_last(t_lexer *lst)
{
	t_lexer	*actuel;

	if (!lst)
		return (NULL);
	actuel = lst;
	if (ft_size(lst) < 2)
		while (actuel->next)
			actuel = actuel->next;
	else
		while (actuel->next->next)
			actuel = actuel->next;
	return (actuel);
}

int	ft_size(t_lexer *lst)
{
	int i;
	t_lexer *actuel;

	actuel = lst;
	i = 0;
	while (actuel)
	{
		actuel = actuel->next;
		i++;
	}
	return (i);
}