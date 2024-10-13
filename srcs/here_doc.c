/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:20:53 by wzeraig           #+#    #+#             */
/*   Updated: 2024/10/05 17:29:14 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	read_and_write(int HD, char *limiteur)
{
	char	*str;

	str = NULL;
	while (1)
	{
		str = readline("> ");
		if (str == NULL)
			return (ERR_READ);
		if (ft_strlen(str) == ft_strlen(limiteur))
		{
			if (!ft_strncmp(str, limiteur, ft_strlen(limiteur)))
			{
				free(str);
				break ;
			}
		}
		write(HD, str, ft_strlen(str));
		write(HD, "\n", 1);
		free(str);
	}
	return (0);
}

int	heredoc(t_all *all, t_redir *redir, char *limiteur)
{
	char	*file_name;

	file_name = limiteur;
	redir->HD = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (redir->HD < 0)
		return (ft_final(all, NULL, ERR_FD));
	if (read_and_write(redir->HD, limiteur))
		return (ERR_READ);
	close(redir->HD);
	redir->HD = open(file_name, O_RDONLY);
	if (redir->HD < 0)
		return (ft_final(all, NULL, ERR_FD));
	return (SUCCESS);
}

int	if_here_doc(t_all *all)
{
	t_redir			*redir;
	t_simple_cmds	*cmds;

	cmds = all->cmds;
	while (cmds)
	{
		redir = cmds->redir;
		while (redir)
		{
			if (redir->token == D_LOWER)
			{
				if (heredoc(all, redir, redir->file_name))
					return (ERR_FD);
			}
			redir = redir->next;
		}
		cmds = cmds->next;
	}
	return (SUCCESS);
}
