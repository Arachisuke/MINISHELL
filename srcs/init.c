/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:00:39 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/30 11:41:46 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	init_all(t_all *all, char **envp)
{
	all->cmds = NULL;
	all->envp = get_env(envp);
	if (!all->envp)
		return (1);
	all->expand = NULL;
	all->lexer = NULL;
	all->line = NULL;
	all->strs = NULL;
	all->tmp_cmds = NULL;
	all->tmp_lexer = NULL;
	return (0);
}