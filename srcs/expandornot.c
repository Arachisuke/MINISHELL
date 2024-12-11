/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandornot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:38:41 by wzeraig           #+#    #+#             */
/*   Updated: 2024/12/11 10:50:01 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_underscore(char *str, int i)
{
	if (str[i] == '$' && str[i + 1] && str[i + 1] == '_')
	{
		while (str[i + 1] && str[i + 1] != ' ')
		{
			str[i++] = ' ';
			str[i] = ' ';
		}
		return (1);
	}
	return (0);
}

int	condition(char *str, int i, int flag)
{
	if (checkredir(str, i))
		return (1);
	if (!flag && str[i] == '$' && str[i + 1] && str[i + 1] == SQ)
		return (str[i] = -87, 1);
	if (!flag && str[i] == '$' && str[i + 1] && str[i + 1] == DQ)
		return (str[i] = -87, 1);
	if (str[i] == '$' && str[i + 1] && ft_isdigit(str[i + 1]))
		return (str[i] = ' ', str[i + 1] = ' ', 1);
	else if (is_underscore(str, i))
		return (1);
	else if (str[i] == '$' && str[i + 1] && str[i + 1] == SQ)
		return (1);
	else if (str[i] == '$' && str[i + 1] && str[i + 1] == DQ)
		return (1);
	else if (str[i] == '$' && str[i + 1] && str[i + 1] == '$')
		return (SUCCESS);
	else if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
		return (SUCCESS);
	else if (str[i] == '$' && str[i + 1] && !ft_isalpha(str[i + 1]))
		return (1);
	else if (str[i] == '$' && str[i + 1])
		return (SUCCESS);
	return (1);
}

void	set_second_expanded(t_expand ***tmp, int i, char *line)
{
	(**tmp)->strexpanded2 = (**tmp)->strexpanded;
	line[i] = -87;
	line[i - 1] = -87;
}

int	fonctionexpand(t_all *all, t_expand **tmp, int *i)
{
	char	*env;
	int		j;
	int		r;

	(*tmp)->i = *i;
	(*i)++;
	r = 0;
	j = *i;
	while (all->line[*i] && (ft_isalnum(all->line[*i]) || all->line[*i] == '_'))
		(*i)++;
	if ((all->line[*i - 1] == -87 || all->line[*i - 1] == '$') && all->line[*i] == '$')
		(*tmp)->strexpanded = ft_pid(all, tmp);
	else if ((all->line[*i - 1] == -87 || all->line[*i - 1] == '$') && all->line[*i] == '?')
		(*tmp)->strexpanded = ft_itoa(all->exit_code);
	env = malloc(sizeof(char) * (*i - j + 1));
	if (!env)
		return (ft_final(all, NULL, NULL, 1));
	(*tmp)->lenbefore = *i - j + 1;
	while (j < *i)
		env[r++] = all->line[j++];
	env[r] = '\0';
	(*tmp)->strtoexpand = env;
	if ((*tmp)->strexpanded)
		set_second_expanded(&tmp, *i, all->line);
	return (SUCCESS);
}

int	ft_expand(t_all *all, int j, char quotes, int flag)
{
	t_expand	*tmp;

	while (all->line[j])
	{
		if ((all->line[j] == SQ || all->line[j] == DQ) && flag == 0)
		{
			quotes = all->line[j];
			all->line[j] = -100;
			flag = 1;
		}
		else if (!condition(all->line, j, flag) && ((flag && quotes == DQ)
				|| !flag))
		{
			tmp = ft_back_expand(&all->expand, ft_new_expand());
			if (fonctionexpand(all, &tmp, &j))
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
