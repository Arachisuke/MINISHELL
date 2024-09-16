/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:34:18 by wzeraig           #+#    #+#             */
/*   Updated: 2023/12/15 16:24:42 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	checkset(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	char	*s1new;
	int		end;
	int		i;

	start = 0;
	end = 0;
	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && checkset(set, s1[start]) == 1)
		start++;
	while (s1[end])
		end++;
	while (end > start && checkset(set, s1[end - 1]) == 1)
		end--;
	s1new = malloc(sizeof(char) * (end - start + 1));
	if (!s1new)
		return (NULL);
	while (start < end)
		s1new[i++] = s1[start++];
	s1new[i] = '\0';
	return (s1new);
}

/* int	main(void)
{
	char str[] = "abcdba";
	printf("la fonction renvoie : %s", ft_strtrim(str, "acb"));
}*/
