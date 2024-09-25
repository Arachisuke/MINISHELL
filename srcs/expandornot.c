/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandornot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:38:41 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/25 12:39:31 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*fonctionexpand(t_all *all, char *str, int i, int flag)
{
	char	*env;
	int		j;
	int		r;

	i++;
	all->expand->i = i;
	r = 0;
	j = i;
	if (flag)
		while (str[i] != DQ && str[i] != SQ && str[i] != '$')
			i++;
	else
		while (str[i] && str[i] != ' ')
			i++;
	env = malloc(sizeof(char) * (i + 1));
	while (j < i)
		env[r++] = str[j++];
	env[r] = '\0';
	all->expand->strtoexpand = env;
	all->expand->lenbefore = j - i;
	return (env);
}

int	ft_expand(t_all *all, int i, char quotes, int flag)
{
	int	j;

	j = i;
	while (all->line[j])
	{
		if ((all->line[j] == SQ || all->line[j] == DQ) && flag == 0)
		// quotes du debut je le supp le quotes et preserve ce quil ya a linterieur
		{
			quotes = all->line[j];
			flag = 1;
			all->line[j] = ' ';
		}
		else if (all->line[j] == '$')
		{
			if ((flag == 1 && quotes == DQ) || flag == 0)
				// si je suis entrecote ca doit etre dq si pas entrecote bah ca expand
				fonctionexpand(all, all->line, j, flag);
		}
		else if (all->line[j] == quotes && flag == 1)
		// quotes de fin je le supp comme ca ca me garde ce quil ya a linterieur
		{
			all->line[j] = ' ';
			flag = 0;
		}
		j++;
	}
	return (0);
}
int	expandornot(t_all *all)
{
	int i;
	char quotes;
	int flag;

	i = 0;
	flag = 0;
	while (all->line[i])
	{
		if (all->line[i] == SQ || all->line[i] == DQ)
		// cest un double ou single cest bon pas oblige que ce soit un word meme un fichier est impacter. meme une redir
		{
			quotes = all->line[i];
			all->line[i] = ' ';
			flag = 1;
			ft_expand(all, i, quotes, flag);
		}
		i++;
	}
	return (0);
}