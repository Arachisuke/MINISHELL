/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:18:46 by ankammer          #+#    #+#             */
/*   Updated: 2024/09/30 13:44:45 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i]) // ca seg ou pas
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return ;
}

char	*free_cmds(t_simple_cmds *cmds) // 2
{
	t_simple_cmds *curr;

	if (!cmds)
		return (NULL);
	curr = cmds;
	while (cmds)
	{
		if (cmds->strs)
			ft_free(cmds->strs);
		if (cmds->redir) // free la node redir avant donc free_redir
			free(cmds->redir);
		curr = cmds->next;
		free(cmds);
		cmds = NULL;
		cmds = curr;
	}
	return (NULL);
}
char	*free_redir(t_redir *redir) // 1
{
	t_redir *curr;

	if (!redir)
		return (NULL);
	curr = redir;
	while (redir) // filename a le meme pointeur que lexer.string
	{
		curr = redir->next;
		free(redir);
		redir = NULL;
		redir = curr;
	}
	return (NULL);
}

char	*free_lexer(t_lexer *lexer) // 3 ou 1
{
	t_lexer *curr;

	if (!lexer)
		return (NULL);
	curr = lexer;
	while (lexer)
	{
		if (lexer->string)
		{
			free(lexer->string);
			lexer->string = NULL;
		}
		curr = lexer->next;
		free(lexer);
		lexer = NULL;
		lexer = curr;
	}
	return (NULL);
}

char	*free_expand(t_expand *expand) // 4
{
	t_expand *curr;

	if (!expand)
		return (NULL);
	curr = expand;
	while (expand)
	{
		// if (expand->strexpanded)
		// free(expand->strexpanded); // dois-je le free ? vu que cest env
		if (expand->strtoexpand)
			free(expand->strtoexpand);
		curr = expand->next;
		free(expand);
		expand = NULL;
		expand = curr;
	}
	return (NULL);
}