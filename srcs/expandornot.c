/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandornot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:38:41 by wzeraig           #+#    #+#             */
/*   Updated: 2024/10/03 17:22:56 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	condition(char *str, int i)
{
	if (checkredir(str, i))
		// si cest un file return1 donc je cree meme pas dexpand
		return (1);
	if (str[i] == '$' && str[i + 1] && str[i + 1] == '$')
		return (1);
	if (str[i] == '$' && str[i + 1] && ft_isdigit(str[i + 1]))
	{
		str[i] = ' ';
		str[i + 1] = ' ';
		return (1);
	}
	if (str[i] == '$' && str[i + 1] && str[i + 1] == SQ)
		return (1);
	if (str[i] == '$' && str[i + 1] && str[i + 1] == DQ)
		return (1);
	if (str[i] == '$' && str[i + 1])
		return (SUCCESS);
	return (1);
}
int	fonctionexpand(t_all *all, t_expand **tmp, int i, int flag)
{
	char	*env;
	int		j;
	int		r;

	j = i;
	(*tmp)->i = i;
	i++;
	r = 0;
	j = i;
	if (flag && all->line[i])
		while (all->line[i] && ft_isalnum(all->line[i]))
			i++;
	while (all->line[i] && ft_isalnum(all->line[i]))
		i++;
	env = malloc(sizeof(char) * (i + 1));
	if (!env)
		return (ft_final(all, NULL, ERR_MALLOC));
	(*tmp)->lenbefore = i - j + 1;
	while (j < i)
		env[r++] = all->line[j++];
	env[r] = '\0';
	(*tmp)->strtoexpand = env;
	return (SUCCESS);
}
int	ft_expand(t_all *all, int j, char quotes, int flag)
{
	t_expand	*tmp;

	while (all->line[++j])
	{
		if ((all->line[j] == SQ || all->line[j] == DQ) && flag == 0)
		{
			quotes = all->line[j];
			flag = 1;
			all->line[j] = all->line[j] * -1;
		}
		else if (!condition(all->line, j) && ((flag && quotes == DQ) || !flag))
		{
			tmp = ft_back_expand(&all->expand, ft_new_expand());
			if (fonctionexpand(all, &tmp, j, flag))
				return (ERR_MALLOC);
		}
		else if (all->line[j] == quotes && flag == 1)
		{
			all->line[j] = all->line[j] * -1;
			flag = 0;
		}
	}
	return (2);
}

int	expandornot(t_all *all)
{
	int		i;
	char	quotes;
	int		flag;

	i = 0;
	flag = 0;
	while (all->line[i])
	{
		if ((all->line[i] == SQ || all->line[i] == DQ || all->line[i] == '$')
			&& flag == 0)
		{
			quotes = all->line[i];
			if (all->line[i] != '$')
			{
				all->line[i] = all->line[i] * -1;
				flag = 1;
			}
			flag = ft_expand(all, i - 1, quotes, flag);
		}
		i++;
	}
	return (flag);
}
