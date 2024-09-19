/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tcmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:21:06 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/19 16:29:45 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_size_cmds(t_simple_cmds *lst)
{
	int				i;
	t_simple_cmds	*actuel;

	actuel = lst;
	i = 0;
	while (actuel)
	{
		actuel = actuel->next;
		i++;
	}
	return (i);
}
t_simple_cmds	*ft_last_cmds(t_simple_cmds *lst)
{
	t_simple_cmds	*actuel;

	if (!lst)
		return (NULL);
	actuel = lst;
	if (ft_size_cmds(lst) < 2)
		while (actuel->next)
			actuel = actuel->next;
	else
		while (actuel->next->next)
			actuel = actuel->next;
	return (actuel);
}
t_simple_cmds	*ft_new_cmds(int i)
{
	t_simple_cmds	*elem;

	elem = malloc(sizeof(t_simple_cmds));
	if (!elem)
		return (NULL);
	elem->is_builtin = 0;
	elem->name = i;
	elem->next = NULL;
	elem->prev = NULL;
	elem->infile = NULL;
	elem->outfile = NULL;
	elem->num_redirections = 0;
	elem->strs = NULL;
	return (elem);
}
void	ft_back_cmds(t_simple_cmds **lst, t_simple_cmds *new)
{
	t_simple_cmds	*last;

	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		if (ft_size_cmds(*lst) == 1)
		{
			last = ft_last_cmds(*lst);
			last->next = new;
			new->next = NULL;
			new->prev = last;
		}
		else
		{
			last = ft_last_cmds(*lst);
			new->prev = last->next;
			last->next->next = new;
		}
	}
}
t_simple_cmds	*create_node_cmds(t_simple_cmds **cmds, int nb_pipe)
{
	int	i;

	i = 0;
	while (nb_pipe >= i)
	{
		if (i == 0)
			*cmds = ft_new_cmds(i);
		else
			ft_back_cmds(cmds, ft_new_cmds(i));
		i++;
	}
	return (*cmds);
}
