/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:31:38 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/15 14:24:16 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	get_current_dir(char *current_directory)
{
	int	i;

	i = 0;
	getcwd(current_directory, PATH_MAX);
	i = ft_strlen(current_directory);
	current_directory[i] = '>';
	current_directory[i + 1] = ' ';
	current_directory[i + 2] = '\0';
}

int	main(int argc, char **argv)
{
	if (argc != 1 && argv)
		return (0);

	char current_directory[PATH_MAX];
	char *line;
	while (1)
	{
		get_current_dir(current_directory);
		line = readline(current_directory); // notre prompt
		printf("line = %s\n", line);
	}
	return (0);
}
