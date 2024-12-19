/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:18:46 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/19 12:45:01 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	if (!strs || !*strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		strs[i] = NULL;
		i++;
	}
	free(strs);
	strs = NULL;
	return ;
}

char	*free_cmds(t_simple_cmds **cmds)
{
	t_simple_cmds	*curr;

	if (!*cmds || !cmds)
		return (NULL);
	curr = *cmds;
	while (*cmds)
	{
		if ((*cmds)->strs)
		{
			free((*cmds)->strs);
			(*cmds)->strs = NULL;
		}
		if ((*cmds)->redir)
			(*cmds)->redir = NULL;
		curr = (*cmds)->next;
		free(*cmds);
		*cmds = NULL;
		*cmds = curr;
	}
	return (NULL);
}

char	*free_redir(t_simple_cmds *cmds)
{
	t_redir			*curr;
	t_simple_cmds	*cmds_tmp;

	if (!cmds)
		return (NULL);
	cmds_tmp = cmds;
	while (cmds_tmp)
	{
		curr = cmds_tmp->redir;
		while (cmds_tmp->redir)
		{
			if (cmds_tmp->redir->fd_here_doc)
				unlink(cmds_tmp->redir->file_name);
			cmds_tmp->redir->file_name = NULL;
			curr = cmds_tmp->redir->next;
			free(cmds_tmp->redir);
			cmds_tmp->redir = NULL;
			cmds_tmp->redir = curr;
		}
		cmds_tmp = cmds_tmp->next;
	}
	return (NULL);
}

char	*free_lexer(t_lexer **lexer)
{
	t_lexer	*curr;

	if (!*lexer || !lexer)
		return (NULL);
	curr = *lexer;
	while (*lexer)
	{
		if ((*lexer)->string)
			(*lexer)->string = NULL;
		curr = (*lexer)->next;
		free(*lexer);
		*lexer = NULL;
		*lexer = curr;
	}
	return (NULL);
}

char	*free_expand(t_expand **expand)
{
	t_expand	*curr;

	if (!*expand || !expand)
		return (NULL);
	curr = *expand;
	while (*expand)
	{
		if ((*expand)->strexpanded)
			(*expand)->strexpanded = NULL;
		if ((*expand)->strexpanded2)
		{
			free((*expand)->strexpanded2);
			(*expand)->strexpanded2 = NULL;
		}
		if ((*expand)->strtoexpand)
			free((*expand)->strtoexpand);
		curr = (*expand)->next;
		free(*expand);
		*expand = NULL;
		*expand = curr;
	}
	return (NULL);
}
