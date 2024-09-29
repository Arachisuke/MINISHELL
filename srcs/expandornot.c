/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandornot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:38:41 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/29 17:56:47 by wzeraig          ###   ########.fr       */
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
		return (0);
	return (1);
}
void	fonctionexpand(t_all *all, t_expand **tmp, int i, int flag)
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
		while (all->line[i] != DQ && all->line[i] != SQ && all->line[i] != '$')
			i++;
	while (all->line[i] && ft_isalnum(all->line[i]))
		i++;
	env = malloc(sizeof(char) * (i + 1));
	(*tmp)->lenbefore = i - j + 1;
	while (j < i)
		env[r++] = all->line[j++];
	env[r] = '\0';
	(*tmp)->strtoexpand = env;
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
		else if (!condition(all->line, j))
		{
			if ((flag == 1 && quotes == DQ) || flag == 0)
			{
				tmp = ft_back_expand(&all->expand, ft_new_expand());
				fonctionexpand(all, &tmp, j, flag);
			}
		}
		else if (all->line[j] == quotes && flag == 1)
		{
			all->line[j] = all->line[j] * -1;
			flag = 0;
		}
	}
	return (2);
}

char	*expandornot(t_all *all)
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
		// cest un double ou single cest bon pas oblige que ce soit un word meme un fichier est impacter. meme une redir
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
	return (all->line);
}
