/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_line2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:55:28 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/17 20:00:31 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_double_redir(char *line, int token, int i)
{
	if (((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<' && line[i
					+ 1] == '<')) && token == 0)
		return (1);
	return (0);
}

int	check_quote_and_redir(char *line, int i, int count)
{
	int	token;

	token = 0;
	while (line[i])
	{
		if (is_double_redir(line, token, i))
		{
			count++;
			i++;
		}
		else if (is_token(line[i]))
		{
			token = 0;
			count++;
		}
		i++;
	}
	return (count);
}

int	firstquotecheck(char *line, int i)
{
	if (line[i] == -34 && line[i + 1] && line[i + 1] == -34 && line[i + 2]
		&& ft_isalpha(line[i + 2]))
		return (i + 2);
	if (line[i] == -39 && line[i + 1] && line[i + 1] == -39 && line[i + 2]
		&& ft_isalpha(line[i + 2]))
		return (i + 2);
	return (i);
}
