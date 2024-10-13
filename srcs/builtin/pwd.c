/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:07:00 by ankammer          #+#    #+#             */
/*   Updated: 2024/10/10 16:19:10 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_pwd(t_simple_cmds *cmds, t_all *all)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		perror("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory");
	else if (cmds->strs[0] && cmds->strs[1][0] == '-')
	{
		ft_printf_fd(2, "bash: pwd: %s : invalid option", cmds->strs[1]);
		free(pwd);
	}
	else
		ft_printf_fd(1, "%s\n", pwd);
	free(pwd);
}
