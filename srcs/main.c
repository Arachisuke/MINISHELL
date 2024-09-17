/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:36 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/17 13:58:57 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_current_dir(void)
{
	int		i;
	char	*line;
	char	current_directory[PATH_MAX];

	i = 0;
	getcwd(current_directory, PATH_MAX);
	i = ft_strlen(current_directory);
	current_directory[i] = '>';
	current_directory[i + 1] = ' ';
	current_directory[i + 2] = '\0';
	line = readline(current_directory);
	return (line);
}

int	main(void)
{
	int		i;
	t_lexer	*lexer;
	char	**strs;
	char	*line;

	line = NULL;
	i = -1;
	while (1)
	{
		line = get_current_dir();
		if (ft_strncmp(line, "exit", 4) == 0)
			break ;
		all_verifs(line);
		strs = malloc_input(line);
		strs = parse_line(line, strs, i);
		lexer = create_node(&lexer, strs);
		node_affichage(lexer);
	}
	return (0);
}
