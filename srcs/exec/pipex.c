/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:43:51 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/19 13:54:37 by ankammer         ###   ########.fr       */
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
		create_process(all, pipex);
	if (pipex->pid[0] == -1 || pipex->pid[pipex->nbrcmd - 1] == -1)
		return (ft_errchild(all, "fork", pipex, 1));
	if (pipex->pid[0] > 0 && pipex->nbrcmd > 1)
		pipex->pid[pipex->nbrcmd - 1] = fork();
	if (pipex->pid[pipex->nbrcmd - 1] == -1)
		return (ft_errchild(all, "fork", pipex, 1));
	if (pipex->nbrcmd > 1 && !pipex->pid[pipex->nbrcmd - 1])
		process_final(all, pipex);
	close_fd(pipex, cmds);
	return (ft_errparent(all, NULL, pipex, wait_childs(pipex->pid[pipex->nbrcmd
					- 1], pipex, all)));
}
