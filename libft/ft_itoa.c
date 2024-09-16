/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:12:16 by wzeraig           #+#    #+#             */
/*   Updated: 2023/12/15 15:45:38 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	getsize(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
	{
		n = 2147483647;
		i++;
	}
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 9)
	{
		i++;
		n = n / 10;
	}
	return (i + 1);
}

int	cutnumber(int n)
{
	if (n == -2147483648)
		return (8);
	if (n < 0)
		n = -n;
	if (n <= 9)
		return (n);
	else
		return (n % 10);
	return (n);
}

char	*ft_itoa(int n)
{
	char	*string;
	int		length;
	int		i;
	int		length2;

	i = 0;
	length = getsize(n);
	length2 = getsize(n);
	string = malloc(sizeof(char) * length + 1);
	if (string == NULL)
		return (NULL);
	if (n < 0)
		i++;
	while (length > 0)
	{
		string[length - 1] = cutnumber(n) + '0';
		length--;
		n = n / 10;
	}
	if (i == 1)
		string[0] = '-';
	string[length2] = '\0';
	return (string);
}

/* int	main(void)
{
	int	n;

	n = 0;
	printf("%s", ft_itoa(2147483647));
}*/
