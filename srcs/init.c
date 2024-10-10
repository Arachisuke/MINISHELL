/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:00:39 by wzeraig           #+#    #+#             */
/*   Updated: 2024/10/05 18:28:50 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	init_all(t_all *all, char **envp)
{
	int	i;

	i = 0;
	all->cmds = NULL;
	all->envp = get_env(envp);
	if (!all->envp)
		return (ERR_ENV);
	all->expand = NULL;
	all->lexer = NULL;
	all->line = NULL;
	all->strs = NULL;
	while (i < 100)
		all->tab[i++] = -1;
	all->tmp_cmds = NULL;
	all->tmp_lexer = NULL;
	return (SUCCESS);
}

void init_parse(t_parse *parse, char *line)
{
	parse->end = 0;
	parse->flag = 0;
	parse->i = skip_spaces(line) - 1;
	parse->j= 0;
	parse->start = 0;
}
