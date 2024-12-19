/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:52:26 by wzeraig           #+#    #+#             */
/*   Updated: 2024/12/19 15:45:46 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*remplir(t_all *all, int start, int end)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = start;
	str = NULL;
	if (end - start == 0)
		str = malloc(sizeof(char) * (1));
	else
		str = malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (ft_final(all, NULL, ERR_INVALID_INPUT, 10), NULL);
	while (end - start > i)
	{
		if (all->line[j] != -100 && all->line[j] < 0)
			all->line[j] = all->line[j] * -1;
		str[i++] = all->line[j++];
	}
	str[i] = '\0';
	str = removequotes(str, all->utils);
	return (str);
}

char	*tokenisation(char *line, int **index)
{
	char	*str;

	if ((line[**index] == '<' && line[**index + 1] == '<')
		|| (line[**index] == '>' && line[**index + 1] == '>'))
	{
		str = malloc(sizeof(char) * 3);
		if (!str)
			return (NULL);
		str[0] = line[**index];
		str[1] = line[**index + 1];
		str[2] = '\0';
		if ((size_t)(index + 2) != ft_strlen(line))
			(**index)++;
	}
	else
	{
		str = malloc(sizeof(char) * 2);
		if (!str)
			return (NULL);
		str[0] = line[**index];
		str[1] = '\0';
	}
	return (str);
}

int	fill_token(t_all *all, char **strs, int *j, int *i)
{
	strs[(*j)++] = tokenisation(all->line, &i);
	if (!strs[(*j) - 1])
		return (1);
	(*i)++;
	return (SUCCESS);
}

void	parsing(t_parse **parse, int *k, t_all *all, char **strs)
{
	if (all->line[(*parse)->i] == -100 || all->line[(*parse)->i] == -124)
		(*parse)->flag = 1;
	(*parse)->start = (*parse)->i;
	(*parse)->end = (*parse)->i;
	while (!is_token_space(all->line[(*parse)->i]) && all->line[(*parse)->i])
	{
		(*parse)->end++;
		(*parse)->i++;
	}
	if ((*parse)->flag)
		fill_tab((*parse)->j, all->tab, &k);
	strs[(*parse)->j++] = remplir(all, (*parse)->start, (*parse)->end);
}

char	**parse_line(t_all *all, char **strs, t_parse *parse)
{
	int	k;

	k = 0;
	while (all->line[parse->i])
	{
		if (!is_token_space(all->line[(parse)->i]) && all->line[(parse)->i])
		{
			parsing(&parse, &k, all, strs);
			parse->flag = 0;
			if (!all->line[(parse)->i])
				break ;
		}
		else if (is_token(all->line[parse->i]))
		{
			if (fill_token(all, strs, &parse->j, &parse->i))
				return (ft_final(all, NULL, NULL, 0), NULL);
		}
		else if (is_space(all->line[parse->i]))
			parse->i++;
	}
	strs[parse->j] = NULL;
	return (strs);
}
