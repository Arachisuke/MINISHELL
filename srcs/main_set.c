/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:45:08 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/17 19:47:27 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_before_while(int argc, char **argv, t_my_env **my_env, int *exit_code)
{
	if (argc != 1 || argv[1])
		return (1);
	*my_env = NULL;
	*exit_code = 0;
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
	if (verif_dir(all->cmds->strs, all))
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
		return (all->exit_code = 0, g_sig = 0, 1);
	catchsignals(all);
	add_history(all->line);
	return (0);
}
