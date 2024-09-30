/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:44:56 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/30 11:34:25 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_arg(t_lexer *curr)
{
	t_lexer	*tmp;
	int		count;

	count = 0;
	tmp = curr;
	if (tmp->token == STRING && !tmp->prev) // premier mot forcement une cmd
		count = 1;
	if (tmp->token == PIPE && tmp->next)
		tmp = tmp->next;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->token == STRING && tmp->prev && (tmp->prev->token == STRING
				|| tmp->prev->token == PIPE))
			count++;
		tmp = tmp->next;
	}
	return (count);
}

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

	if (!tmp_lexer || !tmp_cmds)
		return ;
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

int	passing_next_cmds(t_simple_cmds **tmp, t_lexer *curr, t_simple_cmds **cmds,
		int *i)
{
	(*tmp) = (*tmp)->next;
	(*tmp)->strs = malloc_strs(count_arg(curr));
	if (!(*tmp)->strs)
		return (free_cmds(*cmds), 0);
	*i = 0;
	return (1);
}

int	sort_cmds(t_all *all)
{
	int	i;

	i = 0;
	all->tmp_lexer = all->lexer;
	all->cmds = malloc_cmds_struct(all->tmp_lexer);
	if (!all->cmds)
		return (0);
	all->cmds->strs = malloc_strs(count_arg(all->tmp_lexer));
	if (!all->cmds->strs)
		return (free_cmds(all->cmds), 0);
	all->tmp_cmds = all->cmds;
	while (all->tmp_lexer)
	{
		if (all->tmp_lexer->token != PIPE)
			sort_redir_and_cmds_args(&all, &i);
		else if (!passing_next_cmds(&all->tmp_cmds, all->tmp_lexer, &all->cmds,
				&i))
			return (0);
		if (all->tmp_lexer)
			all->tmp_lexer = all->tmp_lexer->next;
	}
	return (1);
}
