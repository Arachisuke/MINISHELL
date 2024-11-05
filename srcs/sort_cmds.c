/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:44:56 by wzeraig           #+#    #+#             */
/*   Updated: 2024/11/05 12:57:04 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sort_cmds_args(t_lexer *curr, t_simple_cmds **tmp, int *i)
{
	if ((curr->token == STRING && curr->prev && curr->prev->token == STRING)
		|| (curr->token == STRING && (!curr->prev
				|| curr->prev->token == PIPE)))
	{
		(*tmp)->strs[*i] = ft_strdup(curr->string);
		(*i)++;
	}
	if (is_builtin(curr->string))
		(*tmp)->is_builtin = 1;
}

void	sort_redir(t_lexer *tmp_lexer, t_simple_cmds **tmp_cmds)
{
	t_redir	*last_redir;

	ft_back_redir(&(*tmp_cmds)->redir, ft_new_redir());
	last_redir = ft_last_redir((*tmp_cmds)->redir);
	if (tmp_lexer->token != STRING && tmp_lexer->token != PIPE)
		last_redir->token = tmp_lexer->token;
	if (tmp_lexer->next && tmp_lexer->next->token == STRING)
	{
		if (tmp_lexer->token != STRING && tmp_lexer->token != PIPE)
			last_redir->file_name = tmp_lexer->next->string;
		tmp_lexer = tmp_lexer->next;
	}
}

void	sort_redir_and_cmds_args(t_all **all, int *i)
{
	if (((*all)->tmp_lexer)->token == GREATER
		|| ((*all)->tmp_lexer)->token == D_GREATER
		|| ((*all)->tmp_lexer)->token == LOWER
		|| ((*all)->tmp_lexer)->token == D_LOWER)
		sort_redir((*all)->tmp_lexer, &((*all)->tmp_cmds));
	else if (((*all)->tmp_lexer)->token == STRING)
		sort_cmds_args((*all)->tmp_lexer, &((*all)->tmp_cmds), i);
}

int	passing_next_cmds(t_simple_cmds **tmp, t_all *all, int *i)
{
	(*tmp) = (*tmp)->next;
	(*tmp)->strs = malloc_strs(count_arg(all->tmp_lexer));
	if (!(*tmp)->strs)
				return (ft_final(all, NULL, ERR_MALLOC, 1));

	*i = 0;
	return (SUCCESS);
}

int	sort_cmds(t_all *all)
{
	int	i;

	i = 0;
	all->tmp_lexer = all->lexer;
	all->cmds = malloc_cmds_struct(all->tmp_lexer);
	all->cmds->strs = malloc_strs(count_arg(all->tmp_lexer));
	if (!all->cmds->strs || !all->cmds)
				return (ft_final(all, NULL, ERR_MALLOC, 1));

	all->tmp_cmds = all->cmds;
	while (all->tmp_lexer)
	{
		if (all->tmp_lexer->token != PIPE)
			sort_redir_and_cmds_args(&all, &i);
		else if (passing_next_cmds(&all->tmp_cmds, all, &i))
			return (ft_final(all, NULL, ERR_MALLOC, 1));
		if (all->tmp_lexer)
			all->tmp_lexer = all->tmp_lexer->next;
	}
	return (SUCCESS);
}
