/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:38:51 by wzeraig           #+#    #+#             */
/*   Updated: 2024/10/12 16:06:11 by wzeraig          ###   ########.fr       */
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
		/*printf("content = %s\ncurrent = %p\n prev = %p\n next = %p\ntoken =
			%d\n",
		// 	tmp->string, tmp, tmp->prev, tmp->next, tmp->token);
		// tmp = tmp->next; */
	}
}
void	expand_affichage(t_expand *expand)
{
	t_expand	*tmp;

	tmp = expand;
	while (tmp)
	{
		printf("i = %d\nlenbefore = %d\nlenafter= %d\nstrtoexpand= %s\nstrexpanded= %s\n", tmp->i, tmp->lenbefore,
			tmp->lenafter, tmp->strtoexpand, tmp->strexpanded);
		tmp = tmp->next;
		printf("\n");
	}
}
void	cmds_affichage(t_simple_cmds *cmds)
{
	t_simple_cmds	*tmp;
	t_redir			*tmp_redir;
	int				i;

	i = 0;
	tmp = cmds;
	tmp_redir = cmds->redir;
	while (tmp)
	{
		printf("node = %d\nis builtin = %d\n", tmp->name, tmp->is_builtin);
		tmp_redir = tmp->redir;
		if (tmp_redir)
		{
			while (tmp_redir)
			{
				printf("redir = %d\nfile_name = %s\n", tmp_redir->token,
					tmp_redir->file_name);
				tmp_redir = tmp_redir->next;
			}
		}
		printf("\n");
		while (tmp->strs[i])
		{
			printf("strs[%d] = %s\n", i, tmp->strs[i]);
			i++;
		}
		printf("\n");
		i = 0;
		tmp = tmp->next;
		/*printf("content = %s\ncurrent = %p\n prev = %p\n next = %p\ntoken =
			%d\n",
		// 	tmp->string, tmp, tmp->prev, tmp->next, tmp->token);
		// tmp = tmp->next; */
	}
}
