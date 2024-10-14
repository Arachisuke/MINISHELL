/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:00:39 by wzeraig           #+#    #+#             */
/*   Updated: 2024/10/13 19:02:41 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	alloc_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}
char	**ft_myenv(t_all *all, char **env)
{
	int	i;

	i = alloc_env(env);
	all->envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		all->envp[i] = ft_strdup(env[i]);
		i++;
	}
	all->envp[i] = NULL;
	return (all->envp);
}
int	init_all(t_all *all, char **envp)
{
	int	i;

	i = 0;
	all->cmds = NULL;
	all->envp = ft_myenv(all, envp);
	if (!all->envp)
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
}
