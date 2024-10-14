/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:53:17 by wzeraig           #+#    #+#             */
/*   Updated: 2024/10/13 12:09:29 by wzeraig          ###   ########.fr       */
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
	int			i;
	t_expand	*tmp;

	i = -1;
	if (expandornot(all) == 1)
		return (ERR_MALLOC);
	if (!all->expand)
		return (SUCCESS);
	tmp = all->expand;
	while (tmp)
	{
		// while (envp[++i])
		// {
		// 	if ((!ft_strncmp(envp[i], tmp->strtoexpand, tmp->lenbefore - 1))
		// 		&& (envp[i][tmp->lenbefore - 1] == '='))
		// 	{
		// 		tmp->strexpanded = envp[i] + tmp->lenbefore;
		// 		break ;
		// 	}
		// }
		if (ft_strlen(tmp->strtoexpand) != 0)
			tmp->strexpanded = getenv(tmp->strtoexpand);
		tmp = tmp->next;
		// i = 0;
	}
	return (SUCCESS);
}

// iterer while(i)
// flag a 1 les redir
// flag a 0 if flag == 1 et que ya un caractere quelconque