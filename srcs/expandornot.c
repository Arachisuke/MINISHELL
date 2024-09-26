/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandornot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:38:41 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/26 14:59:21 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	fonctionexpand(t_all *all, t_expand **tmp, int i, int flag)
{
	char	*env;
	int		j;
	int		r;

	(*tmp)->i = i;
	i++;
	r = 0;
	j = i;
	if (flag)
		while (all->line[i] != DQ && all->line[i] != SQ && all->line[i] != '$')
			i++;
	else
		while (all->line[i] && ft_isalnum(all->line[i]))
			i++;
	env = malloc(sizeof(char) * (i + 1));
	(*tmp)->lenbefore = i - j + 1;
	while (j < i)
		env[r++] = all->line[j++];
	env[r] = '\0';
	(*tmp)->strtoexpand = env;
}
int	count_expand(t_all *all)
// compter les $ pour voir le nombre de variable et si ya une fausse variable ne pas l'afficher.
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (all->line[i])
	{
		if (all->line[i] == '$')
			count++;
		i++;
	}
	return (count);
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
			all->line[j] = ' ';
		}
		else if (all->line[j] == '$')
		{
			if ((flag == 1 && quotes == DQ) || flag == 0)
			{
				tmp = ft_back_expand(&all->expand, ft_new_expand());
				fonctionexpand(all, &tmp, j, flag);
			}
		}
		else if (all->line[j] == quotes && flag == 1)
		{
			all->line[j] = ' ';
			flag = 0;
		}
	}
	return (2);
}


// int condition(int flag, char *str, char *quotes, int i)
// {
// 	if (str[i] == '$' && str[i + 1] != '$')
// }
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
				all->line[i] = ' ';
				flag = 1;
			}
			flag = ft_expand(all, i - 1, quotes, flag);
		}
		i++;
	}
	return (all->line);
}