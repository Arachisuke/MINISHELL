/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:52:26 by wzeraig           #+#    #+#             */
/*   Updated: 2024/10/03 18:24:56 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_token(char c)
{
	int		i;
	char	*token;

	token = "|><";
	i = 0;
	while (token[i])
	{
		if (token[i] == c)
			return (1);
		i++;
	}
	return (SUCCESS);
}
int	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}
int	is_token_space(char c)
{
	return (is_token(c) || is_space(c));
}
int	count_word_quotes(const char *str, int i, int *compteur)
{
	int	quote;
	int j;

	quote = str[i];
	i++;
	j = i;
	while (str[i] != quote)
	{
		i++;
	}
	if (j == i)
		return(i);
	if (compteur)
		(*compteur)++;
	return (i);
}
int	count_word(const char *str)
{
	int	i;
	int	compteur;

	if (!str)
		return (-1);
	i = firstquotecheck((char *)str) + 1;
	compteur = 0;
	while (str[i])
	{
		if (str[i] < 0)
		{
			if (str[i - 1] && !is_token_space(str[i - 1]) && str[i - 1] > 0)
				compteur++;
			i = count_word_quotes(str, i, &compteur);
		}
		else if ((!is_token_space(str[i]) && is_token_space(str[i + 1]))
			|| (!is_token_space(str[i]) && str[i + 1] == '\0'))
			compteur++;
		i++;
	}
	return (compteur);
}
char	*remplir(t_all *all, int start, int end)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = start;
	if (end - start == 0)
		str = malloc(sizeof(char) * (1));
	else
		str = malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (ft_final(all, NULL, ERR_INVALID_INPUT), NULL);
	while (end - start > i && all->line[j] > -33)
	{
		if (all->line[j] < 0)
			all->line[j] = all->line[j] * -1;
		str[i++] = all->line[j++];
	}
	str[i] = '\0';
	return (str);
}
char	*tokenisation(char **strs, char *line, int *index, int *j)
{
	char	*str;

	if ((line[*index] == '<' && line[*index + 1] == '<') || (line[*index] == '>'
			&& line[*index + 1] == '>'))
	{
		str = malloc(sizeof(char) * 3);
		if (!str)
			free_strs(strs); // sortie d'erreur free puis exit! utiliser erno
		str[0] = line[*index];
		str[1] = line[*index + 1];
		str[2] = '\0';
		if ((size_t)(index + 2) != ft_strlen(line))
			(*index)++;
	}
	else
	{
		str = malloc(sizeof(char) * 2);
		if (!str)
			free_strs(strs); // sortie d'erreur free puis exit! utiliser erno
		str[0] = line[*index];
		str[1] = '\0';
	}
	(*j)++;
	return (str);
}
void	fill_tab(int indice, int *tab, int *i)
{
	tab[*i] = indice;
	// printf("tab[%d] = %d\n", *i, tab[*i]);
	(*i)++;
}

char	**parse_line(t_all *all, char **strs)
{
	int			end;
	int			start;
	int			j;
	int			i;
	int			flag;
	static int	k;

	end = 0;
	flag = 0;
	k = 0;
	start = 0;
	j = 0;
	i = (skip_spaces(all->line) + firstquotecheck(all->line));
	while (all->line[++i])
	{
		if (all->line[i] < 0 && !flag)
			flag = 1;
		else if ((!is_token_space(all->line[i]) && all->line[i]) || (flag && all->line[i] > -33))
		{
			start = i;
			end = i;
			while ((!is_token_space(all->line[i]) && all->line[i] && !flag
					&& all->line[i] > -33) || (flag && all->line[i] > -33))
			{
				end++;
				i++;
			}
			if (flag)
				fill_tab(j, all->tab, &k);
			strs[j++] = remplir(all, start, end);
			if (!all->line[i])
				break ;
			flag = 0;
			if (!strs[j - 1])
				return (NULL);
		}
		else if (is_token(all->line[i]))
			strs[j] = tokenisation(strs, all->line, &i, &j);
	}
	strs[j] = NULL;
	return (strs);
}
