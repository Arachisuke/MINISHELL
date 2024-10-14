/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:00:39 by wzeraig           #+#    #+#             */
/*   Updated: 2024/10/14 17:33:44 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	len_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
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
int	init_all(t_all *all, char **envp)
{
	int	i;

	i = 0;
	all->cmds = NULL;
	all->my_env = ft_myenv(all, envp);
	if (!all->my_env)
		return (ERR_ENV);
	all->expand = NULL;
	all->lexer = NULL;
	all->line = NULL;
	all->strs = NULL;
	while (i < 100)
		all->tab[i++] = -1;
	all->tmp_cmds = NULL;
	all->tmp_lexer = NULL;
	all->shell_id = NULL;
	return (SUCCESS);
}

void	init_parse(t_parse *parse, char *line)
{
	parse->end = 0;
	parse->flag = 0;
	parse->i = skip_spaces(line);
	parse->i = firstquotecheck(line, parse->i) - 1;
	parse->j = 0;
	parse->start = 0;
	parse->quotes = 0;
}
