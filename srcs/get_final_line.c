/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_final_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:44:55 by ankammer          #+#    #+#             */
/*   Updated: 2024/11/27 11:59:08 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_len_expand_line(t_expand *expand)
{
	int	len_total;

	len_total = 0;
	while (expand)
	{
		if (expand->strexpanded)
			len_total += ft_strlen(expand->strexpanded) - expand->lenbefore;
		else
			len_total -= expand->lenbefore;
		expand = expand->next;
	}
	return (len_total);
}

int	str_to_expand_exist(int *i, int **j, char *final_line, t_expand *expand)
{
	int	k;

	if (!expand || !final_line)
		return (1);
	k = 0;
	while (expand && expand->strexpanded[k])
		final_line[(**j)++] = expand->strexpanded[k++];
	*i += expand->lenbefore;
	return (SUCCESS);
}

int	manage_str_to_expand(int *j, t_expand *exp, char *tmp, char *line)
{
	int	i;

	i = 0;
	while (tmp && tmp[i])
	{
		if (exp && i == exp->i)
		{
			if (!exp->strexpanded && (tmp[i] == '$' && ft_isalnum(tmp[i + 1])))
				i += exp->lenbefore;
			else if (exp->strexpanded)
			{
				if (str_to_expand_exist(&i, &j, line, exp))
					return (1);
			}
			else
				line[(*j)++] = tmp[i++];
			if (exp->next)
				exp = exp->next;
		}
		else
			line[(*j)++] = tmp[i++];
	}
	return (SUCCESS);
}

int	fill_final_line(t_expand *expand, char *final_line, char *line_tmp)
{
	int	j;

	j = 0;
	if (!expand || !final_line)
		return (1);
	if (manage_str_to_expand(&j, expand, line_tmp, final_line))
		return (1);
	final_line[j] = '\0';
	return (SUCCESS);
}

int	get_final_line(t_all *all)
{
	char	*line_tmp;
	int		len_total;

	len_total = 0;
	if (!all->expand)
		return (SUCCESS);
	len_total = get_len_expand_line(all->expand) + ft_strlen(all->line);
	if (malloc_final_line(&all->line, len_total, &line_tmp))
		return (ft_final(all, NULL, NULL, 1));
	if (fill_final_line(all->expand, all->line, line_tmp))
	{
		if (line_tmp)
			free(line_tmp);
		return (ft_final(all, NULL, NULL, 1));
	}
	if (line_tmp)
		free(line_tmp);
	return (SUCCESS);
}
