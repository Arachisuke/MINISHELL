/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:01:12 by wzeraig           #+#    #+#             */
/*   Updated: 2024/10/02 10:32:15 by wzeraig          ###   ########.fr       */
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
	if (all->expand)
		free_expand(&all->expand);
	if (all->line)
		free(all->line);
	all->line = NULL;
	all->tmp_cmds = NULL;
	all->tmp_lexer = NULL;
}
int	ft_final(t_all *all, char *error, int sortie)
{
	char *str;

	free_all(all);
	if (sortie == ERR_MALLOC)
		str = "Allocation failed";
	else if (sortie == ERR_SYNTAX)
		str = "syntax error : ";
	else if (sortie == 0)
		return (SUCCESS);
	else if (sortie == ERR_INVALID_INPUT) // a supp
		str = "syntax error : line";
	ft_putstr_fd(str, 1);
	ft_putstr_fd(error, 1);
	ft_putchar_fd('\n', 1);
	return (sortie);
}