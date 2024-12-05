/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:07:00 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/05 13:54:11 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_pwd(t_simple_cmds *cmds, t_all *all)
{
	char	*pwd;

	all->exit_code = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_printf_fd(2, "pwd: error retrieving current directory: %s\n",
			strerror(errno));
	else if (cmds->strs[1] && cmds->strs[1][0] == '-' && cmds->strs[1][1]
		&& cmds->strs[1][1] != '-')
	{
		if (cmds->strs[1][1])
			ft_printf_fd(2, "minishell: pwd: %s : invalid option\n",
				cmds->strs[1]);
		all->exit_code = 1;
	}
	else
		ft_printf_fd(1, "%s\n", pwd);
	if (pwd)
		free(pwd);
}
