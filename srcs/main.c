/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:36 by wzeraig           #+#    #+#             */
/*   Updated: 2024/10/01 18:10:46 by wzeraig          ###   ########.fr       */
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
	if (!line)
		return (NULL);
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	t_all	all;

	if (argc != 1 || argv[1])
		return (0);
	while (1)
	{
		if (init_all(&all, envp))
			continue ;
		all.line = get_current_dir();
		if (!all.line || !*all.line || verif_space(all.line))
			continue ;
		if (ft_strncmp(all.line, "exit", 4) == 0)
			break ; // a supprimer apres!
		add_history(all.line);
		if (verif_quotes(&all, all.line))
			continue ;
		if (find_var(&all, all.envp))
			continue ;
		// expand_affichage(all.expand);
		if (get_final_line(&all))
			continue ;
		if (malloc_input(&all))
			continue ;
		if (!parse_line(&all, all.strs))
			continue ;
		all.line = negative_hollow(all.line);
		all.lexer = create_node(&all.lexer, &all.strs);
		// node_affichage(all.lexer);
		if (state_init(all.lexer, &all))
			continue ;
		if (sort_cmds(&all))
			continue ;
		cmds_affichage(all.cmds);
		if (if_here_doc(&all))
			continue ;
		ft_final(&all, NULL, 0);
	}
	return (0);
}
