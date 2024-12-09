/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:36 by wzeraig           #+#    #+#             */
/*   Updated: 2024/12/09 14:35:27 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		g_sig = 0;

int	check_before_while(int argc, char **argv, t_my_env **my_env, int *exit_code)
{
	if (argc != 1 || argv[1])
		return (1);
	*my_env = NULL;
	*exit_code = 0;
	ft_signals();
	return (0);
}

int	verif_to_final_line(t_all *all)
{
	if (verif_space(all->line, all))
		return (1);
	if (verif_quotes(all, all->line))
		return (1);
	if (find_var(all))
		return (1);
	if (get_final_line(all))
		return (1);
	return (0);
}

int	state_init_to_here_doc(t_all *all)
{
	if (state_init(all->lexer, all))
		return (1);
	if (sort_cmds(all))
		return (1);
	if (if_here_doc(all))
		return (1);
	return (0);
}

void	pipex_or_builtin(t_all *all)
{
	if (all->cmds->strs[0] && (ft_size_cmds(all->cmds) == 1)
		&& is_builtin(all->cmds->strs[0]))
		builtins_or_not(all, all->cmds);
	else if (all->cmds->strs[0])
		ft_pipex(all, all->pipex, all->cmds, all->my_env);
}

int	get_line_and_signals(t_all *all)
{
	get_current_dir(&all->line);
	if (!all->line)
		return (1);
	catchsignals(all);
	add_history(all->line);
	return (0);
}

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
	all->line = removedollarz(all->line);
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

	if (check_before_while(argc, argv, &all.my_env, &all.exit_code))
		return (0);
	while (1)
	{
		if (init_all(&all, envp, &pipex))
			continue ;
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