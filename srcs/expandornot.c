/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandornot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:38:41 by wzeraig           #+#    #+#             */
/*   Updated: 2024/10/13 09:50:07 by wzeraig          ###   ########.fr       */
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

void	is_double_dollar(char *str, int *i)
// est ce qu'on recupere le pid du shell ou on laisse comme ca?
{
	int j;
	int count_dollar;

	count_dollar = 0;
	if (str[*i] == '$' && str[*i + 1] && str[*i + 1] == '$')
	{
		j = *i;
		while (str[j++] == '$')
			count_dollar++;
		if (count_dollar % 2 != 0)
		{
			while (count_dollar-- > 1)
				str[(*i)++] = ' ';
		}
		else
		{
			while (count_dollar-- >= 2)
			{
				str[(*i)++] = ' ';
				str[(*i)] = ' ';
			}
		}
	}
}

int	condition(char *str, int i)
{
	if (checkredir(str, i))
		// si cest un file return1 donc je cree meme pas dexpand
		return (1);
	// is_double_dollar(str, &i);
	if (str[i] == '$' && str[i + 1] && ft_isdigit(str[i + 1]))
	{
		str[i] = ' ';
		str[i + 1] = ' ';
		return (1);
	}
	else if (is_underscore(str, i))
		return (1);
	else if (str[i] == '$' && str[i + 1] && str[i + 1] == SQ)
		return (1);
	else if (str[i] == '$' && str[i + 1] && str[i + 1] == DQ)
		return (1);
	if (str[i] == '$' && str[i + 1] && str[i + 1] == DQ)
		return (1);
	else if (str[i] == '$' && str[i + 1])
		return (SUCCESS);
	return (1);
}

int	fonctionexpand(t_all *all, t_expand **tmp, int *i)
{
	char	*env;
	int		j;
	int		r;

	j = *i;
	(*tmp)->i = *i;
	(*i)++;
	r = 0;
	j = *i;
	while (all->line[*i] && (ft_isalnum(all->line[*i]) || all->line[*i] == '_'))
		// ajout pour gerer l'underscore a la fin
		(*i)++;
	if (all->line[*i - 1] == '$' && all->line[*i] == '$')
		(*tmp)->strexpanded = ft_pid(all);
	env = malloc(sizeof(char) * (*i + 1));
	if (!env)
		return (ft_final(all, NULL, ERR_MALLOC));
	(*tmp)->lenbefore = *i - j + 1;
	while (j < *i)
		env[r++] = all->line[j++];
	env[r] = '\0';
	(*tmp)->strtoexpand = env;
	if ((*tmp)->strexpanded)
		all->line[*i] = ' ';
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
		else if (!condition(all->line, j, flag) && ((flag && quotes == DQ) || !flag))
		{
			tmp = ft_back_expand(&all->expand, ft_new_expand());
			if (fonctionexpand(all, &tmp, &j))
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
