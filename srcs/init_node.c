/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:36:08 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/30 15:12:56 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_lexer	*create_node(t_lexer **lexer, char ***strs)
{
	int	i;

	i = 0;
	while ((*strs)[i])
	{
		if (i == 0)
			*lexer = ft_new((*strs)[i], i);
		else
			ft_back(lexer, ft_new((*strs)[i], i));
		i++;
	}
	i = -1;
	while ((*strs)[++i])
		(*strs)[i] = NULL;
	*strs = NULL;
	return (*lexer);
}
t_lexer	*ft_new(void *content, int i)
{
	t_lexer	*elem;

	elem = malloc(sizeof(t_lexer));
	if (!elem)
		return (NULL);
	elem->string = content;
	elem->next = NULL;
	elem->prev = NULL;
	elem->i = i;
	init_token(elem);
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