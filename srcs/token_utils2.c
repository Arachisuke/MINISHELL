/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:07:20 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/19 13:57:48 by ankammer         ###   ########.fr       */
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
	int	tokenspace;

	j = *i;
	if (j == 0)
		tokenspace = 1;
	else
		tokenspace = is_token_space(str[*i - 1]);
	quote = str[j];
	j++;
	if (!str[j])
		return (*i = j - 1, 0);
	while (str[j] != quote)
	{
		if (str[j] != ' ' && str[j] != quote)
		{
			while (str[j] != quote && str[j])
				j++;
			return (*i = j, tokenspace);
		}
		j++;
	}
	return (*i = j, 0);
}

// int	count_word(const char *str, int i)
// {
// 	int	compteur;
// 	int	flag;

// 	compteur = 0;
// 	flag = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == ' ')
// 			flag = 0;
// 		else if (!is_token_space(str[i]) && str[i] != -100 && !flag)
// 			flag = 1;
// 		if (str[i] < 0)
// 			if (count_word_quotes(str, &i) && str[i + 1] && is_token_space(str[i
// 					+ 1]))
// 				compteur++;
// 		if ((!is_token_space(str[i]) && str[i + 1] && is_token_space(str[i
//+ 1]))
// 				|| ((!is_token_space(str[i]) && str[i + 1] == '\0') && flag))
// 		{
// 			compteur++;
// 			flag = 0;
// 		}
// 		i++;
// 	}
// 	return (compteur);
// }
int	count_word(const char *str, int i, t_utils *s)
{
	s->count = 0;
	s->flag = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			s->flag = 0;
		else if (!is_token_space(str[i]) && str[i] != -100 && !s->flag)
			s->flag = 1;
		if (str[i] == -100)
			if (count_word_quotes(str, &i) && str[i + 1] && is_token_space(str[i
						+ 1]))
				s->count++;
		if (!is_token_space(str[i]) && str[i + 1] && is_token_space(str[i + 1])
			&& s->flag)
		{
			s->count++;
			s->flag = 0;
		}
		if (!is_token_space(str[i]) && str[i + 1] == '\0')
			s->count++;
		i++;
	}
	return (s->count);
}
