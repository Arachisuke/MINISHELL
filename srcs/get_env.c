/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:52:42 by ankammer          #+#    #+#             */
/*   Updated: 2024/10/13 12:39:03 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**get_env(char **envp) // a refaire avec structure env
{
	if (!envp)
		return (NULL);
	return (envp);
}

char	*ft_pid(t_all *all)
{
	int fd;

	if (all->shell_id)
		return (all->shell_id);
	if (all->id)
	{
		all->shell_id = ft_itoa(all->id);
		return (all->shell_id);
	}
	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
		return (ft_final(all, NULL, ERR_FD), NULL);
	all->expand->strexpanded = get_next_line(fd);
	all->id = ft_atoi(all->expand->strexpanded);
	free(all->expand->strexpanded);
	printf("IIIIIIIIIIIIIIID = %d\n", all->id);
	close(fd);
	all->shell_id = ft_itoa(all->id);
	return (all->shell_id);
}