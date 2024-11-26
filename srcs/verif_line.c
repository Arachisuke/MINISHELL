/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:51:02 by wzeraig           #+#    #+#             */
/*   Updated: 2024/11/26 11:00:20 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	return (i);
}

int	verif_space(char *str, t_all *all)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_space(str[i]))
			return (SUCCESS);
		i++;
	}
	return (ft_final(all, NULL, NULL, 1));
}

int	verif_quotes(t_all *all, char *line)
{
	int		i;
	char	quote;
	int		flag;

	quote = 0;
	flag = 0;
	i = 0;
	while (line[i])
	{
		if ((line[i] == SQ || line[i] == DQ) && flag == 0) // debut quotes
		{
			quote = line[i];
			flag = 1;
		}
		else if ((line[i] == ' ' || is_token(line[i])) && flag == 1)
			line[i] = line[i] * -1;
		else if (line[i] == quote && flag == 1) /// fin quotes
			flag = 0;
		i++;
	}
	if (flag == 1)
		return (ft_final(all, NULL, INVALID_SYNTAX, 1));
	return (SUCCESS);
}

int	is_double_redir(char *line, int token, int i) // regler !
{
	if (((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<' && line[i
				+ 1] == '<')) && token == 0)
		return (1);
	return (0);
}

int	check_quote_and_redir(char *line, int i, int count) // le nom est pas coherent avec la fonction.
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
