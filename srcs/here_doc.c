/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:20:53 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/23 18:14:16 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	heredoc(t_redir *redir, char *limiteur, int fd)
{
	char	*str;
	char	*file_name;

	file_name = limiteur;
	str = NULL;
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
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
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	free(str);
	close(fd);
	if (!redir->next)
	{
		fd = open(file_name, O_RDONLY);
		return (fd);
	}
	if (fd < 0)
		return (1); // changer les erreurs
	return (0);
}
int	if_here_doc(t_all *all)
{
	int fd;
	t_redir *redir;
	t_simple_cmds *cmds;
	int the_fd;

	fd = 0;
	the_fd = 0;
	cmds = all->cmds;
	while (cmds)
	{
		redir = cmds->redir;
		while (redir)
		{
			if (redir->token == D_LOWER)
				the_fd = heredoc(redir, redir->file_name, fd);
			// travailler le retour de la fonction pour avoir els bonnes erreurs
			redir = redir->next;
		}
		if (the_fd > 2) // je recupere le premier fd de la premiere node...ensuite je laisserais l'exec parcourir la node pour voir si cest bien la derniere...
			cmds->redir->HD = the_fd;

		cmds = cmds->next;
	}
	if (the_fd > 2)
		// je recupere la valeur vu que c pas le 1 de erreur et le 0/1/2 des redirect de base
		cmds->redir->HD = the_fd;
	// je recupere le fd donc le chemin pour allez dans le file descriptors.
	return (0);
}