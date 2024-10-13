/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:01:12 by wzeraig           #+#    #+#             */
/*   Updated: 2024/10/13 09:50:50 by wzeraig          ###   ########.fr       */
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
	if (all->line)
		free(all->line);
	if (all->shell_id)
		free(all->shell_id);
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
	else if (line[i] == '>')
		while (line[i])
		{
			if (line[i] == '>' && line[i + 1] == '>')
				i++;
			else
				i++;
		}
	if (i == 0)
		i++;
	return (i);
}

int	ft_final(t_all *all, char *error, int sortie)
{
	char	*str;

	str = NULL;

	if (is_triple_redir(all->line) == 3)
		error = "newline";
	if (sortie == ERR_MALLOC)
		str = "Allocation failed";
	else if (sortie == INVALID_SYNTAX)
		str = "minishell: Invalid syntax: ";
	else if (sortie == ERR_SYNTAX)
		str = "minishell : syntax error near unexpected token: `";
	// else if (sortie == 0)
	// 	return (SUCCESS);
	else if (sortie == ERR_INVALID_INPUT) // a supp
		str = "syntax error : line";
	// else
	// 	return (sortie);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(error, 1);
	if (sortie == ERR_SYNTAX)
		ft_putchar_fd('\'', 1);
	ft_putchar_fd('\n', 1);
	free_all(all);
	return (sortie);
}
