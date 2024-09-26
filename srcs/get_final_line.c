/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_final_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:44:55 by ankammer          #+#    #+#             */
/*   Updated: 2024/09/26 13:31:03 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	wrong_env_var(t_expand *expand, int len_total)
{
	while (expand)
	{
		if (!expand->strtoexpand)
			len_total -= expand->lenbefore;
		expand = expand->next;
	}
	return (len_total);
}

int	get_len_expand_line(t_expand *expand)
{
	int			len_before_total;
	int			len_after_total;
	int			len_total;
	t_expand	*tmp_expand;

	len_total = 0;
	tmp_expand = expand;
	len_after_total = 0;
	len_before_total = 0;
	while (tmp_expand)
	{
		if (tmp_expand->strtoexpand)
		{
			len_after_total += tmp_expand->lenafter;
			len_before_total += tmp_expand->lenbefore;
		}
		tmp_expand = tmp_expand->next;
	}
	len_total = len_after_total - len_before_total;
	tmp_expand = expand;
	len_total = wrong_env_var(tmp_expand, len_total);
	return (len_total);
}



void	str_to_expand_exist(int *i, int *j, char *final_line, t_expand *expand)
{
	int	k;

	if (!expand || !final_line)
		return ;
	k = 0;
	while (expand && expand->strexpanded[k])
		final_line[(*j)++] = expand->strexpanded[k++];
	*i += expand->lenbefore;
}

int	fill_final_line(t_expand *expand, char *final_line, char *line_tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!expand || !final_line || !line_tmp)
		return (1);
	while (line_tmp[i])
	{
		if (expand && i == expand->i)
		{
			if (!expand->strtoexpand)
				i += expand->lenbefore;
			else if (expand->strtoexpand)
				str_to_expand_exist(&i, &j, final_line, expand);
			if (expand->next)
				expand = expand->next;
		}
		else
			final_line[j++] = line_tmp[i++];
	}
	final_line[j] = '\0';
	return (0);
}

int	get_final_line(t_all *all)
{
	char	*line_tmp;
	int		len_total;

	if (!all->expand)
		return (0);
	len_total = get_len_expand_line(all->expand) + ft_strlen(all->line);
	if (malloc_final_line(&all->line, len_total, &line_tmp))
		return (1);
	if (fill_final_line(all->expand, all->line, line_tmp))
	{
		if (all->line)
			free(all->line);
		if (line_tmp)
			free(line_tmp);
		return (1);
	}
	free(line_tmp);
	return (0);
}
