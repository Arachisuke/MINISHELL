/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:31:38 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/14 17:21:26 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	test_lecture(void)
{
	char	current_directory[PATH_MAX];
	char	*line;
	int		i;

	line = NULL;
	getcwd(current_directory, PATH_MAX);
	i = ft_strlen(current_directory);
	current_directory[i] = '>';
	current_directory[i + 1] = ' ';
	current_directory[i + 2] = ' ';
	
	line = readline(current_directory); // notre prompt
	printf("line = %s", line);
	return (0);
}
int	main(void)
{
	test_lecture();
}