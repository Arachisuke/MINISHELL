/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:07:20 by ankammer          #+#    #+#             */
/*   Updated: 2024/11/28 12:18:39 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	beforequotes(const char *str, int i)
{
	if (str[i] > 0)
		return (1);
	while (str[i] < 0)
	{
		i--;
	}
	if (is_token_space(str[i]))
		return (1);
	else
		return (0);
}
int	count_word_quotes(const char *str, int *i)
{
	int	quote;
	int	j;

	j = *i;
	quote = str[j];
	j++;
	while (str[j] != quote)
	{
		if (str[j] != ' ' && str[j] != quote)
			return (1);
		j++;
	}
	return (0);
}

int	count_word(const char *str)
{
	int	i;
	int	compteur;
	int	flag;

	if (!str)
		return (-1);
	i = 0;
	compteur = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			flag = 0;
		else if (!is_token_space(str[i]) && str[i] > 0)
			flag = 1;
		if (str[i] < 0 && i > 0)
			if (is_token_space(str[i - 1]) && count_word_quotes(str, &i))
				compteur++;
		if ((!is_token_space(str[i]) && is_token_space(str[i + 1]))
			|| (!is_token_space(str[i]) && str[i + 1] == '\0' && flag))
			compteur++;
		i++;
	}
	return (compteur);
}
