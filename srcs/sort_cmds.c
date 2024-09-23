/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:44:56 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/23 11:44:56 by wzeraig          ###   ########.fr       */
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

void	sort_redir(t_lexer *curr, t_simple_cmds **tmp)
{
	if (curr->token == GREATER || curr->token == D_GREATER)
		(*tmp)->redir_outfile = curr->token;
	else if (curr->token == LOWER || curr->token == D_LOWER)
		(*tmp)->redir_infile = curr->token;
	if (curr->next && curr->next->token == STRING)
	{
		if (curr->token == GREATER || curr->token == D_GREATER)
			(*tmp)->outfile = curr->next->string;
		else if (curr->token == LOWER || curr->token == D_LOWER)
			(*tmp)->infile = curr->next->string;
		curr = curr->next;
	}
}

void	sort_redir_and_cmds_args(t_lexer **curr, t_simple_cmds **tmp, int *i)
{
	if ((*curr)->token == GREATER || (*curr)->token == D_GREATER
		|| (*curr)->token == LOWER || (*curr)->token == D_LOWER)
		sort_redir(*curr, tmp);
	else if ((*curr)->token == STRING)
		sort_cmds_args(*curr, tmp, i);
}

int	passing_next_cmds(t_simple_cmds **tmp, t_lexer *curr, t_simple_cmds **cmds,
		int *i)
{
	(*tmp) = (*tmp)->next;
	(*tmp)->strs = malloc_strs(count_arg(curr));
	if (!(*tmp)->strs)
		return (free_nodes(*cmds), 0);
	*i = 0;
	return (1);
}

int	sort_cmds(t_all *all)
{
	int	i;

	i = 0;
	all->tmp_lexer = &*all->lexer;
	all->cmds = malloc_cmds_struct(all->tmp_lexer);
	if (!all->cmds)
		return (0);
	all->cmds->strs = malloc_strs(count_arg(all->tmp_lexer));
	if (!all->cmds->strs)
		return (free_nodes(all->cmds), 0);
	all->tmp_cmds = all->cmds;
	while (all->tmp_lexer)
	{
		if (all->tmp_lexer->token != PIPE)
			sort_redir_and_cmds_args(&all->tmp_lexer, &all->tmp_cmds, &i);
		else if (!passing_next_cmds(&all->tmp_cmds, all->tmp_lexer, &all->cmds,
				&i))
			return (0);
		if (all->tmp_lexer)
			all->tmp_lexer = all->tmp_lexer->next;
	}
	return (1);
}

int	if_here_doc(t_all *all, t_redir *redir)
{
	while (redir)
	{
		if (redir->token == D_LOWER)               // si heredoc
			here_doc(all, redir, redir->filename); // jenvoie here_doc le lim
		redir = redir->next;
	}
}
int	here_doc(t_all *all, t_redir *redir, char *limiteur)
{
	char	*str;
	char	*file_name;

	file_name = limiteur;
	file_name = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file_name < 0)
		return (1);
	while (1)
	{
		write(1, "> ", 2); // proteger ouuuu
		if (get_next_line(0, &str) == NULL) // si ya un controle D ou autre une ligne vide
			return (1);
		if (ft_strlen(str) == ft_strlen(limiteur) + 1)
		{
			if (!ft_strncmp(str, limiteur, ft_strlen(limiteur)))
				break ;
		}
		write(file_name, str, ft_strlen(str));
		free(str);
	}
	free(str);
	close(file_name);
	if (!redir->next)
		file_name = open(file_name, O_RDONLY);
	if (file_name < 0)
		return (1);
	return (0);
}
