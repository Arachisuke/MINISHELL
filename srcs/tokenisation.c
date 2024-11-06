/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:52:26 by wzeraig           #+#    #+#             */
/*   Updated: 2024/11/06 15:33:25 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*remplir(t_all *all, int start, int end)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = start;
	if (end - start == 0)
		str = malloc(sizeof(char) * (1));
	else
		str = malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (ft_final(all, NULL, ERR_INVALID_INPUT, 10), NULL);
	while (end - start > i && (all->line[j] != -34 && all->line[j] != -39))
	{
		if (all->line[j] == -32)
			all->line[j] = all->line[j] * -1;
		str[i++] = all->line[j++];
	}
	str[i] = '\0';
	return (str);
}
// probleme si !str la fonction continue et ne renvoit pas null
// return (NULL) + verif parseline puis ft_final?
// changer free(strs) -> return (NULL) a voir avec walid!

char	*tokenisation(char *line, int **index)
{
	char	*str;

	if ((line[**index] == '<' && line[**index + 1] == '<')
		|| (line[**index] == '>' && line[**index + 1] == '>'))
	{
		str = malloc(sizeof(char) * 3);
		if (!str)
			return (NULL); // sortie d'erreur free puis exit! utiliser erno
		str[0] = line[**index];
		str[1] = line[**index + 1];
		str[2] = '\0';
		if ((size_t)(index + 2) != ft_strlen(line))
			(**index)++;
	}
	else
	{
		str = malloc(sizeof(char) * 2);
		if (!str)
			return (NULL); // sortie d'erreur free puis exit! utiliser erno
		str[0] = line[**index];
		str[1] = '\0';
	}
	return (str);
}

int	fill_token(t_all *all, char **strs, int *j, int *i)
{
	strs[(*j)++] = tokenisation(all->line, &i);
	if (!strs[(*j) - 1])
		return (1);
	(*i)++;
	return (SUCCESS);
}

void	parsing(t_parse **parse, int *k, t_all *all, char **strs)
{
	{
		(*parse)->start = (*parse)->i;
		(*parse)->end = (*parse)->i;
		while ((!is_token_space(all->line[(*parse)->i])
				&& all->line[(*parse)->i] && !(*parse)->flag
				&& !is_negative_quotes(all->line[(*parse)->i]))
			|| ((*parse)->flag && !is_negative_quotes(all->line[(*parse)->i])))
		{
			(*parse)->end++;
			(*parse)->i++;
		}
		if ((*parse)->flag)
			fill_tab((*parse)->j, all->tab, &k);
		strs[(*parse)->j++] = remplir(all, (*parse)->start, (*parse)->end);
	}
}

// changement dans le while parse++i et init retrait du	-1 pour gerer pipe collee plus reduction ligne parse_line
// parse++i -> probleme lorsque pipe collee incrementait 2 x!
// creation de token utils 2
// voir fonction tokenisation !

char	**parse_line(t_all *all, char **strs, t_parse *parse)
{
	static int	k;

	while (all->line[parse->i])
	{
		if ((is_negative_quotes(all->line[parse->i])) && !parse->flag)
			parse->i += quotes_is_beginning(&parse->flag);
		else if ((!is_token_space(all->line[(parse)->i])
				&& all->line[(parse)->i]) || (parse)->flag)
		{
			parsing(&parse, &k, all, strs);
			if (!all->line[(parse)->i])
				break ;
			if (is_closed_quotes(all->line, &parse, strs))
				return (NULL);
		}
		else if (is_token(all->line[parse->i]))
		{
			if (fill_token(all, strs, &parse->j, &parse->i))
				return (ft_final(all, NULL, ERR_MALLOC, 0), NULL);
		}
		else if (is_space(all->line[parse->i]))
			parse->i++;
	}
	strs[parse->j] = NULL;
	return (strs);
}
