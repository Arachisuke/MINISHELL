/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:42:38 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/16 13:03:27 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_word(const char *str, char *separators)
{
	int	i;
	int	compteur;

	if (!str)
		return (-1);
	i = 0;
	compteur = 0;
	while (str[i])
	{
		if ((str[i] != separators && str[i + 1] == separators) || (str[i] != c
				&& str[i + 1] == '\0'))
			compteur++;
		i++;
	}
	return (compteur);
}

int	ending(const char *str, int i, char *separators)
{
	while (str[i])
	{
		if ((str[i + 1] == separators) || (str[i] != separators && str[i
				+ 1] == '\0'))
		{
			return (i);
		}
		i++;
	}
	return (0);
}

char	**mallocmax(const char *str, char *separators)
{
	char	**strs;
	int		i;
	int		j;

	i = 0;
	j = 0;
	strs = malloc(sizeof(char *) * (count_word(str, separators) + 1));
	if (strs == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] != separators)
		{
			strs[j++] = malloc(sizeof(char) * (ending(str, i, separators) - i
						+ 2));
			if (!strs[j - 1])
				return (NULL);
			i = ending(str, i, separators);
		}
		i++;
	}
	strs[j] = NULL;
	return (strs);
}

char	**ft_split(char const *s, char *separators)
{
	int		i;
	int		j;
	char	**strs;
	int		tmp;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	strs = mallocmax(s, separators);
	if (!strs)
		return (NULL);
	while (s[i])
	{
		tmp = 0;
		if (s[i] != separators)
		{
			while (i <= ending(s, i, separators) && s[i] && s[i] != separators)
				strs[j][tmp++] = s[i++];
			strs[j++][tmp] = '\0';
			i--;
		}
		i++;
	}
	return (strs);
}

/* int	main(void)
{
	ft_split("   tripouille 42 ", ' ');
} */
