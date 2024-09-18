/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:36 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/18 17:58:45 by wzeraig          ###   ########.fr       */
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
	t_lexer			*lexer;
	t_simple_cmds	*cmds;
	char			**strs;
	char			*line;

	line = NULL;
	while (1)
	{
		line = get_current_dir();
		if (ft_strncmp(line, "exit", 4) == 0)
			break ;
		all_verifs(line);
		strs = malloc_input(line);
		strs = parse_line(line, strs);
		lexer = create_node(&lexer, strs);
		node_affichage(lexer);
		state_init(lexer);
		cmds = sort_cmds(lexer);
		cmds_affichage(cmds);

	}
	return (0);
}
