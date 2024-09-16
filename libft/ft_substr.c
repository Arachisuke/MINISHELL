/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:33:39 by wzeraig           #+#    #+#             */
/*   Updated: 2023/12/15 16:25:24 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*snew;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	if (start >= ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	snew = malloc(sizeof(char) * len + 1);
	if (snew == NULL)
		return (NULL);
	while (start + i < ft_strlen(s) && i < len)
	{
		snew[i] = s[start + i];
		i++;
	}
	snew[i] = '\0';
	return (snew);
}
/* int	main(void)
{
	char str[] = "lorem ipsum dolor sit amet";
	printf("%s", ft_substr(str, 7, 0));
}*/
