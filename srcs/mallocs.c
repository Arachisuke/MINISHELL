/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:28:47 by ankammer          #+#    #+#             */
/*   Updated: 2024/11/07 14:56:41 by wzeraig          ###   ########.fr       */
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
		return (free_cmds(&cmds), NULL);
	return (cmds);
}

int	malloc_input(t_all *all)
{
	int	count;
	int	i;

	if (!all->line || !*all->line)
		return (ft_final(all, NULL, ERR_LINE, 1));
	i = skip_spaces(all->line);
	i = firstquotecheck(all->line, i);
	count = count_word(all->line);
		// caractere speciaux non gere car depasse 127 donc negatif
	count = check_quote_and_redir(all->line, i, count);
	printf("COUUUUNT = %d\n", count);
	all->strs = malloc(sizeof(char *) * (count + 1));
	if (!all->strs)
		return (ft_final(all, NULL, ERR_MALLOC, 1));
	return (SUCCESS);
}

int	malloc_final_line(char **line, int len_total, char **line_tmp)
{
	*line_tmp = ft_strdup(*line);
	if (!*line_tmp)
		return (free(*line), 1);
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
		return (free(*line_tmp), 1);
	(*line)[len_total] = '\0';
	return (SUCCESS);
}
