/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:07:20 by ankammer          #+#    #+#             */
/*   Updated: 2024/11/07 16:10:13 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_word_quotes(const char *str, int i, int *compteur)
{
	int	quote;

	quote = str[i];
	i++;
	while (str[i] != quote)
		i++;
	if (compteur)
		(*compteur)++;
	return (i);
}

int	count_word(const char *str)
{
	int	i;
	int	compteur;

	if (!str)
		return (-1);
	i = 0;
	compteur = 0;
	while (str[i])
	{
		if (str[i] == -34 || str[i] == -39)
		{
			if (str[i - 1] && !is_token_space(str[i - 1]))
				compteur++;
			i = count_word_quotes(str, i, &compteur);
		}
		else if ((!is_token_space(str[i]) && is_token_space(str[i + 1]))
			|| (!is_token_space(str[i]) && str[i + 1] == '\0'))
			compteur++;
		i++;
	}
	return (compteur);
}

int	is_closed_quotes(char *line, t_parse **parse, char **strs)
{
	if (line[(*parse)->i] == -34 || line[(*parse)->i] == -39)
		(*parse)->i++;
	(*parse)->flag = 0;
	if (!strs[(*parse)->j - 1])
		return (1);
	return (0);
}
int	quotes_is_beginning(int *flag)
{
	int	i;

	i = 1;
	*flag = 1;
	return (i);
}

