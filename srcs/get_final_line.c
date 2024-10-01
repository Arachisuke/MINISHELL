/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_final_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:44:55 by ankammer          #+#    #+#             */
/*   Updated: 2024/10/01 17:49:12 by wzeraig          ###   ########.fr       */
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
		{
			expand->lenafter = ft_strlen(expand->strexpanded);
			len_total += expand->lenafter - expand->lenbefore;
		}
		else
			len_total -= expand->lenbefore;
		expand = expand->next;
	}
	return (len_total);
}
int	str_to_expand_exist(int *i, int *j, char *final_line, t_expand *expand)
{
	int	k;

	if (!expand || !final_line)
		return (ERR_INVALID_INPUT);
	k = 0;
	while (expand && expand->strexpanded[k])
		final_line[(*j)++] = expand->strexpanded[k++];
	*i += expand->lenbefore;
	return (SUCCESS);
}

int	fill_final_line(t_expand *expand, char *final_line, char *line_tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!expand || !final_line)
		return (ERR_INVALID_INPUT);
	while (line_tmp && line_tmp[i])
	{
		if (expand && i == expand->i)
		{
			if (!expand->strexpanded)
				i += expand->lenbefore;
			else if (expand->strexpanded)
				if (str_to_expand_exist(&i, &j, final_line, expand))
					return (ERR_INVALID_INPUT);
			if (expand->next)
				expand = expand->next;
		}
		else
			final_line[j++] = line_tmp[i++];
	}
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
		return (ft_final(all, NULL, ERR_MALLOC));
	if (fill_final_line(all->expand, all->line, line_tmp))
	{
		if (line_tmp)
			free(line_tmp);
		return (ft_final(all, NULL, ERR_INVALID_INPUT));
	}
	if (line_tmp)
		free(line_tmp);
	return (SUCCESS);
}
