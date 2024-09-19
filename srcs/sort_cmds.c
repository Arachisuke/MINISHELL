/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:44:56 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/19 17:17:29 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_arg(t_lexer *curr)
{
	t_lexer	*tmp;
	int		count;

	count = 1;
	tmp = curr;
	while (tmp)
	{
		if (tmp->string && tmp->string[0] == '-')
			count++;
		tmp = tmp->next;
	}
	return (count);
}
void	sort_cmds_args(t_lexer *curr, t_simple_cmds *tmp, int *i)
{
	if (curr->token == STRING && curr->prev && curr->prev->token == STRING)
	{
		tmp->strs[*i] = ft_strdup(curr->string);
		(*i)++;
	}
	if (is_builtin(curr->string))
		tmp->is_builtin = 1;
}

void	sort_redir(t_lexer *curr, t_simple_cmds *tmp)
{
	if (curr->token == GREATER || curr->token == D_GREATER)
		tmp->redir_outfile = curr->token;
	else if (curr->token == LOWER || curr->token == D_LOWER)
		tmp->redir_infile = curr->token;
	if (curr->next->token == STRING)
	{
		if (curr->token == GREATER || curr->token == D_GREATER)
			tmp->outfile = curr->next->string;
		else if (curr->token == LOWER || curr->token == D_LOWER)
			tmp->infile = curr->next->string;
		curr = curr->next;
	}
}

void	sort_redir_and_cmds_args(t_lexer *curr, t_simple_cmds *tmp, int *i)
{
	if (curr->token == GREATER || curr->token == D_GREATER
		|| curr->token == LOWER || curr->token == D_LOWER)
		sort_redir(curr, tmp);
	else if (curr->token == STRING)
		sort_cmds_args(curr, tmp, i);
}

int	passing_next_cmds(t_simple_cmds *tmp, t_lexer *curr, t_simple_cmds *cmds,
		int *i)
{
	tmp = tmp->next;
	tmp->strs = malloc_strs(count_arg(curr));
	if (!tmp->strs)
		return (free_nodes(cmds), 0);
	*i = 0;
	return (1);
}

t_simple_cmds	*sort_cmds(t_lexer *lexer)
{
	t_simple_cmds	*cmds;
	t_simple_cmds	*tmp;
	t_lexer			*curr;
	int				i;

	i = 0;
	curr = lexer;
	cmds = malloc_cmds_struct(curr);
	if (!cmds)
		return (NULL);
	cmds->strs = malloc_strs(count_arg(curr));
	if (!cmds->strs)
		return (free_nodes(cmds), NULL);
	tmp = cmds;
	while (curr)
	{
		if (curr->token != PIPE)
			sort_redir_and_cmds_args(curr, tmp, &i);
		else if (!passing_next_cmds(tmp, curr, cmds, &i))
			return (NULL);
		curr = curr->next;
	}
	return (cmds);
}
