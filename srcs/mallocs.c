/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:28:47 by ankammer          #+#    #+#             */
/*   Updated: 2024/09/30 12:49:43 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**malloc_strs(int arg_count)
{
	char	**strs;

	strs = malloc(sizeof(char *) * (arg_count + 1));
	if (!strs)
		return (NULL);
	strs[arg_count] = NULL;
	return (strs);
}

t_simple_cmds	*malloc_cmds_struct(t_lexer *current)
{
	int				nb_pipe;
	t_simple_cmds	*cmds;

	nb_pipe = 0;
	cmds = NULL;
	while (current)
	{
		if (current->token == PIPE)
			nb_pipe++;
		current = current->next;
	}
	create_node_cmds(&cmds, nb_pipe);
	if (!cmds)
		return (free_cmds(cmds), NULL);
	return (cmds);
}

int	malloc_input(t_all *all)
{
	int	count;
	int	i;

	if (!all->line || !*all->line)
		return (ERR_INVALID_INPUT);
	i = 0;
	all->strs = NULL;
	count = count_word(all->line);
	while (all->line[i])
	{
		if (is_token(all->line[i]))
		{
			if (is_token(all->line[i + 1]))
				i++;
			count++;
		}
		i++;
	}
	printf("count = %d\n", count);
	all->strs = malloc(sizeof(char *) * (count + 1));
	if (!all->strs)
		return (ERR_MALLOC);
	all->strs[count] = NULL;
	i = 0;
	return (SUCCESS);
}

int	malloc_final_line(char **line, int len_total, char **line_tmp)
{
	*line_tmp = ft_strdup(*line);
	if (!*line_tmp)
		return (free(*line), ERR_MALLOC);
	free(*line);
	*line = NULL;
	if (len_total <= 0)
	{
		free(*line_tmp);
		*line_tmp = NULL;
		*line = malloc(sizeof(char));
		len_total = 0;
	}
	else
		*line = malloc(sizeof(char) * (len_total + 1));
	if (!*line)
		return (free(*line_tmp), ERR_MALLOC);
	(*line)[len_total] = '\0';
	return (SUCCESS);
}