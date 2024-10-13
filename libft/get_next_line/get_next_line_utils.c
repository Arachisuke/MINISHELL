/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 08:44:06 by wzeraig           #+#    #+#             */
/*   Updated: 2024/10/12 18:02:30 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strduper(const char *s)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] != '\n' && s[i])
		i++;
	if (s[i] == '\n')
		i++;
	if (i == 0)
		return (NULL);
	str = malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\n' && s[i])
	{
		str[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*strcut(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\n' && s[i])
		i++;
	if (s[i] == '\n')
		i++;
	while (s[i])
	{
		s[j++] = s[i++];
	}
	s[j] = '\0';
	return (s);
}

char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*joinfreenew(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (s2 == NULL)
		return (NULL);
	while (s2[i] != '\n' && s2[i])
		i++;
	if (s2[i] == '\n')
		i++;
	str = malloc(sizeof(char) * (i + 1 + ft_strlen(s1)));
	if (str == NULL || i == 0)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j] != '\n' && s2[j])
		str[i++] = s2[j++];
	if (s2[j] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	free(s1);
	return (str);
}
