/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:50:37 by wzeraig           #+#    #+#             */
/*   Updated: 2024/11/26 13:08:22 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_all(t_all *all)
{
	if (all->strs)
	{
		free_strs(all->strs);
		all->strs = NULL;
	}
	if (all->cmds)
		free_redir(all->cmds);
	if (all->cmds)
		free_cmds(&all->cmds);
	if (all->lexer)
		free_lexer(&all->lexer);
	if (all->expand)
		free_expand(&all->expand);
	if (all->shell_id)
		free(all->shell_id);
	if (all->line)
		free(all->line);
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
	free_all(all);
	return (sortie);
}
void	msg_error(t_all *all, char *msgerror, char *error)
{
	if (is_triple_redir(all->line) == 3)
		ft_putstr_fd("newline", 2);
	if (!ft_strncmp(msgerror, ERR_SYNTAX, 26))
		ft_printf_fd(2, "%s%s'", msgerror, error);
	else if (!ft_strncmp(msgerror, ERR_EGAL, 20))
		ft_printf_fd(2, "%s%s': not a valid identifier", msgerror, error);
	else if (!ft_strncmp(msgerror, ERR_BASE, 14))
		ft_printf_fd(2, "%s%s': command not found", msgerror, error);
	else
		ft_putstr_fd(msgerror, 2);
	ft_putchar_fd('\n', 1);
}