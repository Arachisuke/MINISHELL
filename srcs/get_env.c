/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:52:42 by ankammer          #+#    #+#             */
/*   Updated: 2024/10/12 18:25:42 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**get_env(char **envp) // a refaire avec structure env
{
	if (!envp)
		return (NULL);
	return (envp);
}

char *ft_pid(t_all *all)
{
	int fd;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
		return (ft_final(all, NULL, ERR_FD), NULL);
	all->shell_id = get_next_line(fd);
	close(fd);
	return(all->shell_id);
}