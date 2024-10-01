/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:52:26 by wzeraig           #+#    #+#             */
/*   Updated: 2024/10/01 13:59:24 by wzeraig          ###   ########.fr       */
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
	return (0);
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
	int	j;

	quote = str[i];
	i++;
	j = i;
	while (str[i] != quote)
	{
		i++;
	}
	if (j == i)
		return (i);
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
		if (str[i] < 0)
		{
			if (!is_token_space(str[i]) && is_token_space(str[i + 1]))
			i = count_word_quotes(str, i, &compteur);
		}
		if ((!is_token_space(str[i]) && is_token_space(str[i + 1]))
			|| (!is_token_space(str[i]) && str[i + 1] == '\0'))
			compteur++;
		i++;
	}
	return (compteur);
}
char	*remplir(char **strs, char *line, int start, int end)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = start;
	if (ft_strlen(line) == (size_t)end + 1)
		end = ft_strlen(line);
	str = malloc(sizeof(char) * (end - start + 1));
	if (!str)
		ft_free(strs); // sortie d'erreur free puis exit! utiliser erno
	while (end - start > i && line[j] > -33)
	{
		if (line[j] < 0)
			line[j] = line[j] * -1;
		str[i] = line[j];
		i++;
		j++;
	}
	str[i] = '\0';
	printf("str = %s\n", str);
	return (str);
}
char	*tokenisation(char **strs, char *line, int *index, int *j)
{
	char	*str;

	if ((line[*index] == '<' || line[*index] == '>') && (line[*index + 1] == '<'
			|| line[*index + 1] == '>'))
	{
		str = malloc(sizeof(char) * 3);
		if (!str)
			ft_free(strs); // sortie d'erreur free puis exit! utiliser erno
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
			ft_free(strs); // sortie d'erreur free puis exit! utiliser erno
		str[0] = line[*index];
		str[1] = '\0';
	}
	(*j)++;
	printf("str = %s\n", str);
	return (str);
}

char	**parse_line(char *line, char **strs)
{
	int	end;
	int	start;
	int	j;
	int	i;
	int	flag;

	end = 0;
	flag = 0;
	start = 0;
	j = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] < 0 && !flag)
			flag = 1;
		else if ((!is_token_space(line[i]) && line[i]) || flag)
		{
			start = i;
			end = i;
			while ((!is_token_space(line[i]) && line[i + 1] && !flag)
				|| (flag == 1 && line[i] > -33))
			{
				end++;
				i++;
			}
			flag = 0;
			strs[j++] = remplir(strs, line, start, end);
		}
		if (is_token(line[i]))
			strs[j] = tokenisation(strs, line, &i, &j);
	}
	strs[j] = NULL;
	return (strs);
}
