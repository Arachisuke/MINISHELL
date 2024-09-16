/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:47:42 by wzeraig           #+#    #+#             */
/*   Updated: 2023/12/15 15:46:00 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	checkstr(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!big && len == 0)
		return (0);
	if (little[i] == '\0')
		return ((char *)big);
	while (len > i && big[i] != '\0')
	{
		if (little[j] == big[i + j])
		{
			j = 0;
			while (little[j] == big[i + j] && len > (i + j) && big[i + j])
			{
				if (little[j++ + 1] == '\0')
					return ((char *)big + i);
			}
		}
		i++;
	}
	return (NULL);
}

/*int	main(void)
{
	char little[] = "aabc";
	char big[] = "aaabcabcd";

	printf("Yannfonction renvoie : %s\n", ft_strnstryann(big, little, -1));
	printf("la fonction renvoie : %s\n", ft_strnstr(big, little, -1));
}*/
