/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:52:26 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/16 18:57:19 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

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
	str = malloc(sizeof(char) * (end - start + 1));
	while (end - start > i)
	{
		str[i] = line[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
char	*tokenisation(char c, int *j)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	(*j)++;
	return (str);
}

int	main(void)
{
	int		i;
	char	*line;
	char	**strs;
	int		j;
	int		r;
	int		g;
	int		flag;

	r = -1;
	j = 0;
	flag = 0;
	i = 0;
	g = 0;
	line = "<infile cat|ls -la>>outfile";
	strs = malloc_input(line);
	while (line[++r])
	{
		if (!is_token_space(line[r]) && line[r])
		{
			i = r;
			g = r;
		}
		while (!is_token_space(line[r]) && line[r])
		{
			r++;
			i++;
			flag = 1;
		}
		if (flag == 1)
		{
			strs[j++] = remplir(line, g, i);
			flag = 0;
		}
		if (is_token(line[r]))
			strs[j] = tokenisation(line[r], &j);
	}
	i = 0;
	// while (strs[i])
	// {
	// 	printf("strs[%d] = %s", i, strs[i]);
	// 	i++;
	// }
	// test = 0;
	// while(test < 10)
	// {
	// 	printf("strs[%d] = %s", test, strs[test]);
	// 	test++;
	// }
}

// while (line[r])
// {
// 	while (!is_token(line[r]))
// 		strs[j][i++] = line[r++];
// 	i = 0;
// 	if (is_token(line[r]))
// 		strs[++j][i] = line[r++];
// }