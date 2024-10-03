/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:18:46 by ankammer          #+#    #+#             */
/*   Updated: 2024/10/03 11:00:40 by wzeraig          ###   ########.fr       */
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

char	*free_cmds(t_simple_cmds **cmds) // 2
{
	t_simple_cmds *curr;

	if (!*cmds || !cmds)
		return (NULL);
	curr = *cmds;
	while (*cmds)
	{
		if ((*cmds)->strs)
			free_strs((*cmds)->strs);
		if ((*cmds)->redir) // free la node redir avant donc free_redir
			(*cmds)->redir = NULL;
		curr = (*cmds)->next;
		free(*cmds);
		*cmds = NULL;
		*cmds = curr;
	}
	return (NULL);
}
char	*free_redir(t_redir **redir) // 1
{
	t_redir *curr;

	if (!*redir || !redir)
		return (NULL);
	curr = *redir;
	while (*redir) // filename a le meme pointeur que lexer.string
	{
		(*redir)->file_name = NULL;
		curr = (*redir)->next;
		free(*redir);
		*redir = NULL;
		*redir = curr;
	}
	return (NULL);
}

char	*free_lexer(t_lexer **lexer) // 3 ou 1
{
	t_lexer *curr;

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

char	*free_expand(t_expand **expand) // 4
{
	t_expand *curr;

	if (!*expand || !expand)
		return (NULL);
	curr = *expand;
	while (*expand)
	{
		// if ((*expand)->strexpanded)
		// free((*expand)->strexpanded); // dois-je le free ? vu que cest env
		if ((*expand)->strtoexpand)
			free((*expand)->strtoexpand);
		curr = (*expand)->next;
		free(*expand);
		*expand = NULL;
		*expand = curr;
	}
	return (NULL);
}