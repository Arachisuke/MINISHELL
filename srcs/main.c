/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:36 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/25 12:43:31 by wzeraig          ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_all	all;
	
	while (1)
	{
		get_env(envp, &all);
		all.line = get_current_dir();
		if (!*all.line || !all.line) // que faire quand ya rien ?
			continue ;
		if (ft_strncmp(all.line, "exit", 4) == 0)
			break ;
		if (all.line)
			add_history(all.line);
		if (!all_verifs(all.line))
			return(printf("error syntax"), 1);
		if (!malloc_input(&all))
			return (errno);
		if (!all.strs)
			return (errno);
		if (!parse_line(all.line, all.strs))
			return (errno);
		all.lexer = create_node(&all.lexer, all.strs);
		// node_affichage(all.lexer);
		state_init(all.lexer);
		if (!sort_cmds(&all))
			return (errno);
		cmds_affichage(all.cmds);
		if_here_doc(&all);
		expandornot(&all);
	}
	return (0);
}
