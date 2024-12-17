/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macos <macos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:00:39 by wzeraig           #+#    #+#             */
/*   Updated: 2024/12/14 16:15:06 by macos            ###   ########.fr       */
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

char	*ft_pid(t_all *all, t_expand **tmp)
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
	(*tmp)->strexpanded = get_next_line(fd);
	all->id = ft_atoi((*tmp)->strexpanded);
	free((*tmp)->strexpanded);
	close(fd);
	all->shell_id = ft_itoa(all->id);
	return (all->shell_id);
}

void	init_utils(t_all *all)
{
	all->utils->count = 0;
	all->utils->flag = 0;
	all->utils->i = 0;
	all->utils->j = 0;
	all->utils->value2 = NULL;
	g_sig = 0;
}

int	init_all(t_all *all, char **envp, t_pipex *pipex, t_utils *utils)
{
	int	i;

	i = 0;
	all->cmds = NULL;
	all->expand = NULL;
	all->lexer = NULL;
	all->pipex = pipex;
	all->line = NULL;
	all->strs = NULL;
	while (i < 100)
		all->tab[i++] = -1;
	all->tmp_cmds = NULL;
	all->tmp_lexer = NULL;
	all->cmds = NULL;
	all->shell_id = NULL;
	all->id = 0;
	all->pipex->nbrcmd = 0;
	if (!all->my_env)
		all->my_env = ft_myenv(all, envp);
	if (!all->my_env)
		return (1);
	all->utils = utils;
	all->fd_in = 0;
	init_utils(all);
	return (SUCCESS);
}

void	init_parse(t_parse *parse, char *line)
{
	parse->end = 0;
	parse->flag = 0;
	parse->i = skip_spaces(line);
	parse->i = firstquotecheck(line, parse->i);
	parse->j = 0;
	parse->start = 0;
	parse->quotes = 0;
}

void	get_current_dir(char **line)
{
	int		i;
	char	current_directory[PATH_MAX];

	i = 0;
	if (!getcwd(current_directory, PATH_MAX))
	{
		chdir(getenv("OLDPWD"));
		if (!getcwd(current_directory, PATH_MAX))
		{
			*line = readline("minishell> ");
			return;
		}
	}
	i = ft_strlen(current_directory);
	current_directory[i] = '>';
	current_directory[i + 1] = ' ';
	current_directory[i + 2] = '\0';
	*line = readline(current_directory);
}
