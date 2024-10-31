/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:53:17 by wzeraig           #+#    #+#             */
/*   Updated: 2024/10/31 15:17:26 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	checkredir(char *line, int i)
{
	int	j;
	int	flag;

	j = -1;
	flag = 0;
	while (i > ++j)
	{
		if (flag && ((line[j] == '|' || line[j] == ' ') && (line[j - 1] != '<'
					&& line[j - 1] != '>')))
			flag = 0;
		else if (flag == 0 && (line[j] == '<' || line[j] == '>'))
			flag = 1;
	}
	return (flag);
}

int	find_var(t_all *all)
{
	t_expand	*tmp;
	t_my_env *tmpenv;

	if (expandornot(all) == 1)
		return (ERR_MALLOC);
	if (!all->expand)
		return (SUCCESS);
	tmp = all->expand;
	tmpenv = all->my_env;
	while (tmp)
	{
		if (ft_strlen(tmp->strtoexpand) != 0)
		{
			while (tmpenv)
			{
				if (!ft_strncmp(tmpenv->key, tmp->strtoexpand,
						tmp->lenbefore - 1))
					tmp->strexpanded = tmpenv->value;
				tmpenv = tmpenv->next;
			}
		}
		tmp = tmp->next;
		tmpenv = all->my_env;
	}
	return (SUCCESS);
}

// iterer while(i)
// flag a 1 les redir
// flag a 0 if flag == 1 et que ya un caractere quelconque