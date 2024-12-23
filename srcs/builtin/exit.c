/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:22:26 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/17 15:37:15 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	str_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(t_simple_cmds *cmds, t_all *all)
{
	if (ft_size_cmds(all->cmds) == 1)
		ft_printf_fd(1, "exit\n");
	if (cmds->strs[1])
	{
		if (!str_is_numeric(cmds->strs[1]))
		{
			all->exit_code = ft_atoi(cmds->strs[1]);
			if (cmds->strs[2])
			{
				ft_printf_fd(2, "minishell: exit: too many arguments\n");
				return (1);
			}
		}
		else
		{
			ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
				cmds->strs[1]);
			all->exit_code = 2;
		}
	}
	if (ft_size_cmds(all->cmds) != 1)
		return (ft_errchild(all, NULL, all->pipex, all->exit_code));
	free_env(&all->my_env);
	ft_final(all, NULL, NULL, all->exit_code);
	exit(all->exit_code);
}
