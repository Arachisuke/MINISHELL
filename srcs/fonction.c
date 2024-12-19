/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:38:51 by wzeraig           #+#    #+#             */
/*   Updated: 2024/12/18 14:43:59 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	node_affichage(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	while (tmp)
	{
		printf("Node = %d\ncontent = %s\n token = %d\n", tmp->i, tmp->string,
			tmp->token);
		tmp = tmp->next;
		printf("content = %s\ncurrent = %p\n prev = %p\n next = %p\ntoken = %d\n",
			tmp->string, tmp, tmp->prev, tmp->next, tmp->token);
		tmp = tmp->next;
	}
}

void	expand_affichage(t_expand *expand)
{
	t_expand	*tmp;

	tmp = expand;
	while (tmp)
	{
		printf("i = %d\nlenbe = %d\nlenaf= %d\nstrto= %s\nstrex = %s\n ",
			tmp->i, tmp->lenbefore, tmp->lenafter,
			tmp->strtoexpand, tmp->strexpanded);
		tmp = tmp->next;
		printf("\n");
	}
}

void	print_redir(t_redir **tmp_redir, int fd_here_doc)
{
	if (*tmp_redir)
	{
		while (*tmp_redir)
		{
			printf("redir = %d\nfile_name = %s\nheredoc = %d\n",
				(*tmp_redir)->token, (*tmp_redir)->file_name,
				fd_here_doc);
			*tmp_redir = (*tmp_redir)->next;
		}
	}
}

void	cmds_affichage(t_simple_cmds *cmds)
{
	t_simple_cmds	*tmp;
	t_redir			*tmp_redir;
	int				i;

	i = -1;
	tmp = cmds;
	tmp_redir = cmds->redir;
	while (tmp)
	{
		printf("node = %d\nis builtin = %d\n", tmp->index, tmp->is_builtin);
		tmp_redir = tmp->redir;
		print_redir(&tmp_redir, tmp->redir->fd_here_doc);
		printf("\n");
		while (tmp->strs[++i])
			printf("strs[%d] = %s\n", i, tmp->strs[i]);
		printf("\n");
		tmp = tmp->next;
		printf("content = %s\ncurrent = %p\n prev = %p\n next = %p\ntoken = %d\n",
			tmp->strs[0], tmp, tmp->prev, tmp->next, tmp_redir->token);
		tmp = tmp->next;
	}
}
