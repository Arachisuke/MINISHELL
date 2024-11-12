/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:32:10 by wzeraig           #+#    #+#             */
/*   Updated: 2024/11/12 11:56:47 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pipex(t_all *all, t_pipex *pipex, t_simple_cmds *cmds, t_my_env *envp)
{
	init_struct(pipex, cmds, envp);
	init_variable(pipex);
	pipex->pid[0] = fork();
	if (pipex->pid[0] == -1)
		ft_error(all, "fork", 1);
	if (pipex->pid[0] == 0)
		first_process(all, envp);
	if (pipex->pid[0] > 0 && argc > 5)
		create_process(all);
	if (pipex->pid[0] == -1 || pipex->pid[argc - 4 - pipex.ifhdoc] == -1)
		ft_error(all, "fork", 1);
	if (pipex->pid[0] > 0)
		pipex->pid[argc - 4 - pipex.ifhdoc] = fork();
	if (pipex->pid[argc - 4 - pipex.ifhdoc] == -1)
		ft_error(all, "fork", 1);
	if (pipex->pid[argc - 5 - pipex.ifhdoc] && pipex->pid[argc - 4 - pipex.ifhdoc] == 0)
		process_final(all, argc);
	close_fd(argc, all);
	ft_error(all, NULL, wait_childs(pipex->pid[argc - 4 - pipex.ifhdoc], all));
}
