/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:20:53 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/24 12:14:58 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	heredoc(t_redir *redir, char *limiteur)
{
	char	*str;
	char	*file_name;

	file_name = limiteur;
	str = NULL;
	redir->HD = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (redir->HD < 0)
		return (1);
	while (1)
	{
		str = readline("> ");
		if (str == NULL)
			return (1);
		if (ft_strlen(str) == ft_strlen(limiteur))
		{
			if (!ft_strncmp(str, limiteur, ft_strlen(limiteur)))
				break ;
		}
		write(redir->HD, str, ft_strlen(str));
		write(redir->HD, "\n", 1);
		free(str);
	}
	free(str);
	close(redir->HD);
	redir->HD = open(file_name, O_RDONLY);
	if (redir->HD < 0)
		return (1); // changer les erreurs
	return (0);
}
int	if_here_doc(t_all *all)
{
	t_redir *redir;
	t_simple_cmds *cmds;

	cmds = all->cmds;
	while (cmds)
	{
		redir = cmds->redir;
		while (redir)
		{
			if (redir->token == D_LOWER)
			{
				if (heredoc(redir, redir->file_name))// travailler le retour de la fonction pour avoir els bonnes erreurs
					return(errno); // ERREURFD;
			}
			redir = redir->next;
		}
		cmds = cmds->next;
	}

	return (0);
}
