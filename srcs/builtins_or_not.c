/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_or_not.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:55:15 by wzeraig           #+#    #+#             */
/*   Updated: 2024/11/05 15:55:45 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	builtins_or_not(t_all *all, t_simple_cmds *cmds)
{
	if (!ft_strncmp(cmds->strs[0], "cd", 2) && cmds->is_builtin)
		return ;
	else if (!ft_strncmp(cmds->strs[0], "echo", 4) && cmds->is_builtin)
		return ;
	else if (!ft_strncmp(cmds->strs[0], "env", 4) && cmds->is_builtin)
		return ;
	else if (!ft_strncmp(cmds->strs[0], "exit", 4) && cmds->is_builtin)
		return ;
	else if (!ft_strncmp(cmds->strs[0], "export", 6) && cmds->is_builtin)
		ft_export(all, cmds->strs);
	else if (!ft_strncmp(cmds->strs[0], "pwd", 3) && cmds->is_builtin)
		return ;
	else if (!ft_strncmp(cmds->strs[0], "unset", 5) && cmds->is_builtin)
		return (ft_unset(all, cmds->strs));
}