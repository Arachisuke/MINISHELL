/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:52:26 by wzeraig           #+#    #+#             */
/*   Updated: 2024/10/12 15:02:59 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_word_quotes(const char *str, int i, int *compteur)
{
	int	quote;

	quote = str[i];
	i++;
	while (str[i] != quote)
		i++;
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
	i = 0;
	compteur = 0;
	while (str[i])
	{
		if (str[i] == -39 || str[i] == -34)
		{
			if (str[i - 1] && !is_token_space(str[i - 1]))
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
	while (end - start > i && (all->line[j] != -34 && all->line[j] != -39)) // jai change le || par &&
	{
		if (all->line[j] == -32)
			all->line[j] = all->line[j] * -1;
		str[i++] = all->line[j++];
	}
	str[i] = '\0';
	return (str);
}

char	*tokenisation(char **strs, char *line, int *index)
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
	return (str);
}

void	parsing(t_parse **parse, int *k, t_all *all, char **strs)
{
	{
		(*parse)->start = (*parse)->i;
		(*parse)->end = (*parse)->i;
		while ((!is_token_space(all->line[(*parse)->i])
				&& all->line[(*parse)->i] && !(*parse)->flag
				&& all->line[(*parse)->i] > -33) || ((*parse)->flag
				&& all->line[(*parse)->i] > -33))
		{
			(*parse)->end++;
			(*parse)->i++;
		}
		if ((*parse)->flag)
			fill_tab((*parse)->j, all->tab, &k);
		strs[(*parse)->j++] = remplir(all, (*parse)->start, (*parse)->end);
	}
}
char	**parse_line(t_all *all, char **strs, t_parse *parse)
{
	static int k;

	while (all->line[++parse->i])
	{
		if ((all->line[parse->i] == -34 || all->line[parse->i] == -39) && !parse->flag)
		{
			parse->flag = 1;
		}
		else if ((!is_token_space(all->line[(parse)->i])
				&& all->line[(parse)->i]) || (parse)->flag)
		{
			parsing(&parse, &k, all, strs);
			if (!all->line[(parse)->i])
				break ;
			(parse)->flag = 0;
			if (!strs[(parse)->j - 1])
				return (NULL);
		}
		else if (is_token(all->line[parse->i]))
			strs[parse->j++] = tokenisation(strs, all->line, &parse->i);
	}
	strs[parse->j] = NULL;
	return (strs);
}
