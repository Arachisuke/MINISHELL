/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:00:39 by wzeraig           #+#    #+#             */
/*   Updated: 2024/11/06 10:23:15 by wzeraig          ###   ########.fr       */
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
	int	fd;

	if (all->shell_id)
		return (all->shell_id);
	if (all->id)
	{
		all->shell_id = ft_itoa(all->id);
		return (all->shell_id);
	}
	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
		return (ft_final(all, NULL, ERR_FD, 1), NULL);
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
		return (ft_final(all, NULL, ERR_FD, 1), NULL);
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
	if (!all->my_env->next)
		all->my_env = ft_myenv(all, envp);
	if (!all->my_env)
		return (1);
	all->expand = NULL;
	all->lexer = NULL;
	all->line = NULL;
	all->strs = NULL;
	while (i < 100)
		all->tab[i++] = -1;
	all->tmp_cmds = NULL;
	all->tmp_lexer = NULL;
	all->shell_id = NULL;
	all->exit_code = 0;
	all->id = 0;
	return (SUCCESS);
}

void	init_parse(t_parse *parse, char *line)
{
	parse->end = 0;
	parse->flag = 0;
	parse->i = skip_spaces(line);
	parse->i = firstquotecheck(line, parse->i); // 1
	parse->j = 0;
	parse->start = 0;
	parse->quotes = 0;
}
void	get_current_dir(char **line)
{
	int i;
	char current_directory[PATH_MAX];

	i = 0;
	getcwd(current_directory, PATH_MAX);
	i = ft_strlen(current_directory);
	current_directory[i] = '>';
	current_directory[i + 1] = ' ';
	current_directory[i + 2] = '\0';
	*line = readline(current_directory);
}