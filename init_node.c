/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:36:08 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/16 12:05:18 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_node(t_lexer **lexer, char *line)
{
	parse_line(line , lexer);
}

int	parse_line(char *line, t_lexer **lexer)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i])
	{
		while (is_space(line[i]))
			i++;
		if (flag == 0)
		{
			*lexer = ft_new(line[i]);
			flag = 1;
		}
		else
			ft_back(lexer, ft_new(line[i]));
	}
}
t_list	*ft_new(void *content)
{
	t_lexer	*elem;

	elem = malloc(sizeof(t_lexer));
	if (!elem)
		return (NULL);
	elem->string = content;
	elem->next = NULL;
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
		if (ft_lstsize(*lst) < 2)
		{
			last = ft_last(*lst);
			last->next = new;
			last->prev = *lst;
		}
		else
		{
			last = ft_last(*lst);
			new->prev = last;
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
	if (ft_lstsize(lst) < 2)
		while (actuel->next)
			actuel = actuel->next;
	else
		while (actuel->next->next)
			actuel = actuel->next;
	return (actuel);
}