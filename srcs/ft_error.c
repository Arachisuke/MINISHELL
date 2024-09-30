/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:01:12 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/30 14:15:41 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_all(t_all *all)
{
	if (all->cmds && all->cmds->redir)
		free_redir(all->cmds->redir);
	if (all->cmds)
		free_cmds(all->cmds);
	if (all->lexer) // a tester avant redir
		free_lexer(all->lexer);
	if (all->expand)
		free_expand(all->expand);
	if (all->strs)
		ft_free(all->strs);
	if (all->line)
		free(all->line);
}
void	ft_final(t_all *all, char *str, int fd)
{
	free_all(all);
	ft_putstr_fd(str, fd); // afficher la str et la valeur de retour ?
}