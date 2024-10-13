/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:36 by wzeraig           #+#    #+#             */
/*   Updated: 2024/10/13 09:46:16 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_current_dir(char **line)
{
	int		i;
	char	current_directory[PATH_MAX];

	i = 0;
	getcwd(current_directory, PATH_MAX);
	i = ft_strlen(current_directory);
	current_directory[i] = '>';
	current_directory[i + 1] = ' ';
	current_directory[i + 2] = '\0';
	*line = readline(current_directory);
}

int	main(int argc, char **argv, char **envp)
{
	t_parse	parse;
	t_all	all;

	if (argc != 1 || argv[1])
		return (SUCCESS);
	while (1)
	{
		if (init_all(&all, envp))
			continue ;
		get_current_dir(&all.line);
		if (!all.line || !*all.line)
			continue ;
		if (ft_strncmp(all.line, "exit", 4) == 0)
			break ; // a supprimer apres!
		add_history(all.line);
		if (verif_space(all.line, &all))
			continue ;
		if (verif_quotes(&all, all.line))
			continue ;
		//	printf("lineafterverif = %s\n", all.line);
		if (find_var(&all, all.envp))
			continue ;
		expand_affichage(all.expand);
		//	printf("lineafterfind_var = %s\n", all.line);
		if (get_final_line(&all))
			// a partir d'ici line n'as jamais change donc pas besoin de faire de verif de line par contre line change apres cette fonction
			continue ;
		// printf("linefinal = %s\n", all.line);
		if (verif_space(all.line, &all))
			continue ;
		if (malloc_input(&all))
			continue ;
		init_parse(&parse, all.line);
		if (!parse_line(&all, all.strs, &parse))
			// ici cest strs qui recupere les donne de line
			continue ;
		// i = -1;
		// while(all.strs[++i])
		// 	printf("strs[%d] = %s\n",i,  all.strs[i]);
		// printf("lineafterparseline = %s\n", all.line);
		// all.line = negative_hollow(all.line);
		all.lexer = create_node(&all, &all.lexer, &all.strs);
		// node_affichage(all.lexer);       /// strs et line..et all
		if (state_init(all.lexer, &all))
			// token dans une chaine de caractere mais sans guillemet comment le gerer!
			continue ;
		if (sort_cmds(&all))
			continue ;
		cmds_affichage(all.cmds);
		if (if_here_doc(&all))
			continue ;
		ft_final(&all, NULL, 0);
	}
	return (SUCCESS);
}
