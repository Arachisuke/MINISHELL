/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:36 by wzeraig           #+#    #+#             */
/*   Updated: 2024/12/19 13:51:33 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_sig = 0;

int	verif_space_to_parse_line(t_all *all, t_parse *parse)
{
	if (verif_space(all->line, all))
		return (1);
	if (malloc_input(all))
		return (1);
	init_parse(parse, all->line);
	if (!parse_line(all, all->strs, parse))
		return (1);
	return (0);
}

int	minish(t_all *all, t_parse *parse)
{
	if (verif_to_final_line(all))
		return (1);
	all->line = removedollarz(all->line, all->utils);
	if (verif_space_to_parse_line(all, parse))
		return (1);
	all->lexer = create_node(all, &all->lexer, &all->strs);
	if (state_init_to_here_doc(all))
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_parse	parse;
	t_all	all;
	t_pipex	pipex;
	t_utils	utils;

	if (check_before_while(argc, argv, &all.my_env, &all.exit_code))
		return (0);
	while (1)
	{
		if (init_all(&all, envp, &pipex, &utils))
			continue ;
		ft_signals();
		if (get_line_and_signals(&all))
			break ;
		if (minish(&all, &parse))
			continue ;
		pipex_or_builtin(&all);
		ft_final(&all, NULL, NULL, all.exit_code);
	}
	free_env(&all.my_env);
	ft_printf_fd(1, "exit\n");
	return (SUCCESS);
}

// expand_affichage(all.expand);
// cmds_affichage(all.cmds);
// printf("afterremove = %s\n", all.line);
// node_affichage(all.lexer); /// strs et line..et all
// printf("before = %s\n", all.line);
// printf("afterremove = %s\n", all.line);
// printf("lineafterget = %s\n", all.line);
