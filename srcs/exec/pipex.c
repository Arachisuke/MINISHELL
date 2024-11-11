/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:32:10 by wzeraig           #+#    #+#             */
/*   Updated: 2024/11/11 15:32:53 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main(t_all *all, int argc, t_simple_cmds *cmds, char **envp)
{
	init_struct(&data, argc, argv, envp);
	init_variable(argc, &data);
	data.id[0] = fork();
	if (data.id[0] == -1)
		ft_error(&data, "fork", 1);
	if (data.id[0] == 0)
		first_process(&data, argv, envp);
	if (data.id[0] > 0 && argc > 5)
		create_process(argv, &data);
	if (data.id[0] == -1 || data.id[argc - 4 - data.ifhdoc] == -1)
		ft_error(&data, "fork", 1);
	if (data.id[0] > 0)
		data.id[argc - 4 - data.ifhdoc] = fork();
	if (data.id[argc - 4 - data.ifhdoc] == -1)
		ft_error(&data, "fork", 1);
	if (data.id[argc - 5 - data.ifhdoc] && data.id[argc - 4 - data.ifhdoc] == 0)
		process_final(&data, argv, argc);
	close_fd(argc, &data);
	ft_error(&data, NULL, wait_childs(data.id[argc - 4 - data.ifhdoc], &data));
}
