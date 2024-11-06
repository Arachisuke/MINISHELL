/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:07:00 by ankammer          #+#    #+#             */
/*   Updated: 2024/11/06 14:03:03 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_pwd(t_simple_cmds *cmds)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_printf_fd(2, "pwd: error retrieving current directory: %s\n",
			strerror(errno));
	else if (cmds->strs[1] && cmds->strs[1][0] == '-')
	{
		if (cmds->strs[1][1])
			ft_printf_fd(2, "bash: pwd: %s : invalid option\n", cmds->strs[1]);
	}
	else
		ft_printf_fd(1, "%s\n", pwd);
	free(pwd);
}
