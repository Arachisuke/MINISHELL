/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_t_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:09:41 by ankammer          #+#    #+#             */
/*   Updated: 2024/11/14 15:31:04 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_redir	*ft_last_redir(t_redir *lst)
{
	t_redir	*actuel;

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
	elem->fd_here_doc = 0;
	elem->ifhdoc = 0;
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
		last = ft_last_redir(*lst);
		last->next = new;
	}
}
