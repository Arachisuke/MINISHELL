/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:36 by wzeraig           #+#    #+#             */
/*   Updated: 2024/12/03 13:59:26 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_sig = 0;

int	main(int argc, char **argv, char **envp)
{
	t_parse	parse;
	t_all	all;
	t_pipex	pipex;

	all.my_env = NULL;
	all.exit_code = 0;
	if (argc != 1 || argv[1])
		return (0);
	ft_signals();
	while (1)
	{
		if (init_all(&all, envp, &pipex))
			continue ;
		get_current_dir(&all.line);
		if (!all.line)
			break ;
		catchsignals(&all);
		add_history(all.line);
		if (verif_space(all.line, &all))
			continue ;
		if (verif_quotes(&all, all.line))
			continue ;
		if (find_var(&all))
			continue ;
		// expand_affichage(all.expand);
		if (get_final_line(&all))
			continue ;
		//	printf("lineafterget = %s\n", all.line);
		if (verif_space(all.line, &all))
			continue ;
		if (malloc_input(&all))
			continue ;
		// printf("before = %s\n", all.line);
		all.line = removequotes1(all.line); // jenleve les quotes
		// printf("afterremove = %s\n", all.line);
		init_parse(&parse, all.line);
		if (!parse_line(&all, all.strs, &parse))
			continue ;
		// node_affichage(all.lexer); /// strs et line..et all
		all.lexer = create_node(&all, &all.lexer, &all.strs);
		if (state_init(all.lexer, &all))
			continue ;
		if (sort_cmds(&all))
			continue ;
		//	printf("afterremove = %s\n", all.line);
		// cmds_affichage(all.cmds);
		if (if_here_doc(&all))
			continue ;
		if (all.cmds->strs[0] && (ft_size_cmds(all.cmds) == 1)
			&& is_builtin(all.cmds->strs[0]))
			builtins_or_not(&all, all.cmds);
		else if (all.cmds->strs[0])
			ft_pipex(&all, all.pipex, all.cmds, all.my_env);
		ft_final(&all, NULL, NULL, 1);
	}
	free_env(&all.my_env);
	return (SUCCESS);
}
