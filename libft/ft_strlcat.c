/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:18:21 by wzeraig           #+#    #+#             */
/*   Updated: 2023/12/05 12:45:53 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	destlen;

	j = 0;
	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	j = ft_strlen((char *)dest);
	destlen = ft_strlen((char *)dest);
	if (j < size - 1)
	{
		while (src[i] && j < size - 1)
			dest[j++] = src[i++];
		dest[j] = '\0';
	}
	if (size <= destlen)
		destlen = size;
	return (destlen + ft_strlen(src));
}

/*int	main(void)
{
	char dest[] = "Salut";
	char src[] = "Walid";

	printf("la tienne %zu\n", ft_strlcat(dest, src, 9));
}*/