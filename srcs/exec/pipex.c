/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:32:10 by wzeraig           #+#    #+#             */
/*   Updated: 2024/11/21 11:57:07 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pipex(t_all *all, t_pipex *pipex, t_simple_cmds *cmds, t_my_env *envp)
{
	init_struct(all, pipex, cmds);
	init_variable(pipex, all);
	if (envlist_envchar(pipex, envp))
		return (ft_errchild(all, "malloc", pipex, 1));
	parsing_pipex(pipex, pipex->env);
	pipex->pid[0] = fork();
	if (pipex->pid[0] == -1)
		return (ft_errchild(all, "fork", pipex, 1));
	if (pipex->pid[0] == 0 && pipex->nbrcmd == 1)
		return (onecmd(all, pipex, cmds));
	if (pipex->pid[0] == 0)
		first_process(all, pipex, cmds);
	if (pipex->pid[0] > 0 && pipex->nbrcmd > 2)
		create_process(all, pipex, cmds);
	if (pipex->pid[0] == -1 || pipex->pid[pipex->nbrcmd - 1] == -1)
		return (ft_errchild(all, "fork", pipex, 1));
	if (pipex->pid[0] > 0 && pipex->nbrcmd > 1)
		pipex->pid[pipex->nbrcmd - 1] = fork();
	if (pipex->pid[pipex->nbrcmd - 1] == -1)
		return (ft_errchild(all, "fork", pipex, 1)); // free envp
	if (pipex->nbrcmd > 1 && !pipex->pid[pipex->nbrcmd - 1])
		process_final(all, pipex, cmds);
	close_fd(pipex, cmds); // envp
	return (ft_errparent(all, NULL, pipex, wait_childs(pipex->pid[pipex->nbrcmd
				- 1], pipex)));
}
