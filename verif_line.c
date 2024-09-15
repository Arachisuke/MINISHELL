/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:51:02 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/15 17:40:37 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SQ '\''
#define DQ '\"'

char	*verif_quotes(char *line)
{
	int		i;
	char	quote;
	int		flag;

	i = 0;
	flag = 0;
	i = -1;
	while (line[++i])
	{
		if ((line[i] == '\'' || line[i] == '"') && flag == 0)
		{
			quote = line[i];
			flag = 1;
		}
		else if (line[i] != quote && flag == 1)
			line[i] *= -1;
		else if (line[i] == quote && flag == 1)
			flag = 0;
	}
	if (flag == 1)
		return(0);
	return (1);
}
int	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	verif_redirection(void)
{}
char *verif_space(char *line)
{
	int i;

	i = 0;
		if (!line)
		return (1);
	while (is_space(line[i]))
		i++;
	if (i == ft_strlen(line))
		return (1);
	return(0)
}

int all_verifs(char *line)
{
	verif_space(line);
	verif_quotes(line);

	
}