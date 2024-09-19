/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:52:26 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/19 12:33:39 by wzeraig          ###   ########.fr       */
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
		if ((!is_token_space(str[i]) && is_token_space(str[i + 1]))
			|| (!is_token_space(str[i]) && str[i + 1] == '\0'))
			compteur++;
		i++;
	}
	return (compteur);
}
char	*remplir(char *line, int start, int end)
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
		return(NULL);
	while (end - start > i)
	{
		str[i] = line[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
char	*tokenisation(char *line, int *index, int *j)
{
	char	*str;

	if ((line[*index] == '<' || line[*index] == '>') && (line[*index + 1] == '<' || line[*index + 1] == '>'))
	{
		str = malloc(sizeof(char) * 3);
		str[0] = line[*index];
		str[1] = line[*index + 1];
		str[2] = '\0';
		if ((size_t)(index + 2) != ft_strlen(line))
			(*index)++;
	}
	else
	{
		str = malloc(sizeof(char) * 2);
		str[0] = line[*index];
		str[1] = '\0';
	}
	(*j)++;
	return (str);
}

char	**parse_line(char *line, char **strs) 
{
	int end;
	int start;
	int j;
	int i;

	end = 0;
	start = 0;
	j = 0;
	i = -1;
	while (line[++i])
	{
		if (!is_token_space(line[i]) && line[i])
		{
			start = i;
			end = i;
			while (!is_token_space(line[i]) && line[i + 1])
			{
				end++;
				i++;
			}
			strs[j++] = remplir(line, start, end);
		}
		if (is_token(line[i]))
			strs[j] = tokenisation(line, &i, &j);
	}
	return (strs);
}