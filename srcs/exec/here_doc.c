/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:19:25 by wzeraig           #+#    #+#             */
/*   Updated: 2024/11/14 14:49:43 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// void	here_doc(t_data *data, char **argv)
// {
// 	char	*str;

// 	data->ifhdoc = 1;
// 	data->heredoc = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (data->heredoc < 0)
// 		return(ft_errchild(data, "opendoc", pipex,  1));
// 	while (1)
// 	{
// 		write(1, "heredoc> ", 9);
// 		if (get_next_line(0, &str) == NULL)
// 			return(ft_errchild(data, NULL, pipex, 1));
// 		if (ft_strlen(str) == ft_strlen(argv[2]) + 1)
// 		{
// 			if (!ft_strncmp(str, argv[2], ft_strlen(argv[2])))
// 				break ;
// 		}
// 		write(data->heredoc, str, ft_strlen(str));
// 		free(str);
// 	}
// 	free(str);
// 	close(data->heredoc);
// 	data->heredoc = open(".heredoc_tmp", O_RDONLY);
// 	if (data->heredoc < 0)
// 		return(ft_errchild(data, "opendoc2", pipex, 1));
// }
