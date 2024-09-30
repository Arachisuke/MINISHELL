/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:36 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/30 14:11:07 by ankammer         ###   ########.fr       */
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

	if (argc != 1 || init_all(&all, envp) || argv[1]) // si ya un arg on stop!
		return (0);                                  
			// ya que lui comme structure a init, si ya pas d'envp je return!
	while (1)
	{
		init_all(&all, envp);
		all.line = get_current_dir();
		if (!all.line || !*all.line) // si ya pas de malloc, si le malloc est vide
			continue ;
		if (ft_strncmp(all.line, "exit", 4) == 0)
			break ; // a supprimer apres!
		if (all.line)
			add_history(all.line);
		if (all_verifs(all.line)) // verif line ?
			return (errno);
		if (find_var(&all, all.envp))
			return (0); // erreur dans le expandornot!
		// expand_affichage(all.expand);
		if (get_final_line(&all))
			return (errno);
		printf("line = %s\n", all.line);
		if (malloc_input(&all))
			continue ;
		if (!parse_line(all.line, all.strs)) // renvoie NULL
			return (errno);
		all.lexer = create_node(&all.lexer, all.strs);
		// node_affichage(all.lexer);
		if (state_init(all.lexer))
			return (ERR_INVALID_INPUT);
		if (!sort_cmds(&all))
			return (errno);
		cmds_affichage(all.cmds);
		if_here_doc(&all);
		ft_final(&all, NULL, 0);
	}
	return (0);
}
