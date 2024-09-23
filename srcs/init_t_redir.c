/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_t_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:09:41 by ankammer          #+#    #+#             */
/*   Updated: 2024/09/23 15:05:15 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_size_redir(t_redir *lst) // a modifier
{
	int i;
	t_redir *actuel;

	actuel = lst;
	i = 0;
	while (actuel)
	{
		actuel = actuel->next;
		i++;
	}
	return (i);
}
t_redir	*ft_last_redir(t_redir *lst) // a modifier
{
	t_redir *actuel;

	if (!lst)
		return (NULL);
	actuel = lst;
	while (actuel->next)
		actuel = actuel->next;
	return (actuel);
}

t_redir	*ft_new_redir(void)
{
	t_redir	*elem;

	elem = malloc(sizeof(t_redir));
	if (!elem)
		return (NULL);
	elem->file_name = NULL;
	elem->token = 6;
	elem->next = NULL;
	return (elem);
}

void	ft_back_redir(t_redir **lst, t_redir *new)
{
	t_redir	*last;

	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		if (ft_size_redir(*lst) == 1)
		{
			last = ft_last_redir(*lst);
			last->next = new;
			new->next = NULL;
		}
		else
		{
			last = ft_last_redir(*lst);
			last->next = new;
		}
	}
}
