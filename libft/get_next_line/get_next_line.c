/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:41:50 by wzeraig           #+#    #+#             */
/*   Updated: 2024/10/13 10:43:19 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	static char	left[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = read_file(fd, buf, left, line);
	return (line);
}

char	*read_file(int fd, char *buf, char *left, char *line)
{
	int	bytes_read;

	bytes_read = 1;
	line = ft_strdup("");
	while (!ft_strchr(left, ' '))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		buf[bytes_read] = '\0';
		if (ft_strchr(buf, ' '))
			break ;
		left = ft_strcpy(left, buf);
		line = joinfreenew(line, left);
	}
	return (line);
}
