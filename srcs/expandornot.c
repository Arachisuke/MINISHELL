/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandornot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:38:41 by wzeraig           #+#    #+#             */
/*   Updated: 2024/12/18 11:58:21 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_second_expanded(t_expand ***tmp, int i, char *line)
{
	(**tmp)->strexpanded2 = (**tmp)->strexpanded;
	line[i] = -87;
	line[i - 1] = -87;
}

int	fonctionexpand(t_all *all, t_expand **tmp, int *i, char *line)
{
	char	*env;
	int		j;
	int		r;

	(*tmp)->i = *i;
	(*i)++;
	r = 0;
	j = *i;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	if ((line[*i - 1] == -87 || line[*i - 1] == '$') && line[*i] == '$')
		(*tmp)->strexpanded = ft_pid(all, tmp);
	else if ((line[*i - 1] == -87 || line[*i - 1] == '$') && line[*i] == '?')
		(*tmp)->strexpanded = ft_itoa(all->exit_code);
	env = malloc(sizeof(char) * (*i - j + 1));
	if (!env)
		return (ft_final(all, NULL, NULL, 1));
	(*tmp)->lenbefore = *i - j + 1;
	while (j < *i)
		env[r++] = line[j++];
	env[r] = '\0';
	(*tmp)->strtoexpand = env;
	if ((*tmp)->strexpanded)
		set_second_expanded(&tmp, *i, line);
	return (SUCCESS);
}

void	set_minus_hundred(char *quotes, int *flag, char *c)
{
	*quotes = *c;
	*c = -100;
	*flag = 1;
}

int	ft_expand(t_all *all, int j, char quotes, int flag)
{
	t_expand	*tmp;

	while (all->line[j])
	{
		if ((all->line[j] == SQ || all->line[j] == DQ) && flag == 0)
			set_minus_hundred(&quotes, &flag, &all->line[j]);
		else if (!condition(all->line, j, flag) && ((flag && quotes == DQ)
				|| !flag))
		{
			tmp = ft_back_expand(&all->expand, ft_new_expand());
			if (fonctionexpand(all, &tmp, &j, all->line))
				return (ft_final(all, NULL, NULL, 1));
			j--;
		}
		else if (all->line[j] == quotes && flag == 1)
		{
			flag = 0;
			all->line[j] = -100;
		}
		j++;
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
			&& !flag)
		{
			quotes = all->line[i];
			if (all->line[i] != '$')
			{
				all->line[i] = -100;
				flag = 1;
			}
			flag = ft_expand(all, i, quotes, flag);
		}
		i++;
	}
	return (flag);
}
