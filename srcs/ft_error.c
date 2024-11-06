/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:01:12 by wzeraig           #+#    #+#             */
/*   Updated: 2024/11/06 09:33:15 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_all(t_all *all)
{
	if (all->cmds && all->cmds->redir)
		free_redir(&all->cmds->redir);
	if (all->cmds)
		free_cmds(&all->cmds);
	if (all->lexer) // a tester avant redir
		free_lexer(&all->lexer);
	if (all->strs)
		free_strs(all->strs);
	if (all->expand)
		free_expand(&all->expand);
	if (all->shell_id)
		free(all->shell_id);
	if (all->line)
		free(all->line);
	all->line = NULL;
	all->tmp_cmds = NULL;
	all->tmp_lexer = NULL;
}

int	is_triple_redir(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '<')
	{
		while (line[i])
		{
			if (line[i] == '<' && line[i + 1] == '<')
				i++;
			else
				i++;
		}
	}
	if (i == 0)
		i++;
	return (i);
}

int	ft_final(t_all *all, char *error, char *msgerror, int sortie)
{
	if (msgerror)
		msg_error(all, msgerror, error);
	if (sortie)
		free_all(all);
	return (sortie);
}
void	msg_error(t_all *all, char *msgerror, char *error)
{
	if (is_triple_redir(all->line) == 3)
		ft_putstr_fd("newline", 2);
	if (!ft_strncmp(msgerror, ERR_SYNTAX, 20))
		ft_printf_fd(2, "%s%s'", msgerror, error);
	else if (!ft_strncmp(msgerror, ERR_EGAL, 20))
		ft_printf_fd(2, "%s%s': not a valid identifier", msgerror, error);
	else if (!ft_strncmp(msgerror, ERR_EXPORT, 2))
		ft_printf_fd(2, "%s%s': command not found", msgerror, error);
	else
		ft_putstr_fd(msgerror, 2);
	ft_putchar_fd('\n', 1);
}