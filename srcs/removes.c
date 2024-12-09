/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:32:32 by wzeraig           #+#    #+#             */
/*   Updated: 2024/12/09 13:53:39 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*removequotes(char *line, t_utils *s)
{
	char	*newline;

	s->i = -1;
	s->count = 0;
	newline = NULL;
	while (line[++(s->i)])
	{
		if (line[s->i] == -100)
			s->count++;
	}
	if (s->count == 0)
		return (line);
	newline = malloc(sizeof(char) * (ft_strlen(line) - s->count + 1));
	if (!newline)
		return (NULL);
	s->i = -1;
	s->j = 0;
	while (line[++(s->i)])
	{
		if (line[s->i] == -100)
			continue ;
		newline[s->j++] = line[s->i];
	}
	return (newline[s->j] = '\0', free(line), newline);
}

int	count_quotes(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == -100 && line[i + 1] && line[i + 1] == -100)
		{
			i++;
			count = count + 2;
		}
		i++;
	}
	return (count);
}

char	*removequotes1(char *line, t_utils *s)
{
	char	*newline;

	newline = NULL;
	s->i = 0;
	s->count = count_quotes(line);
	if (s->count == 0)
		return (line);
	newline = malloc(sizeof(char) * (ft_strlen(line) - s->count + 1));
	if (!newline)
		return (NULL);
	s->i = -1;
	s->j = 0;
	while (line[++(s->i)])
	{
		if (line[s->i] == -100 && line[s->i + 1] && line[s->i + 1] == -100)
		{
			(s)->i++;
			continue ;
		}
		newline[s->j++] = line[s->i];
	}
	return (newline[s->j] = '\0', free(line), newline);
}

char	*removedollarz(char *line, t_utils *s)
{
	char	*newline;
	s->i = -1;

	s->count = 0;
	newline = NULL;
	while (line[++(s->i)])
	{
		if (line[s->i] == -87)
			s->count++;
	}
	if (s->count == 0)
		return (removequotes1(line, s));
	newline = malloc(sizeof(char) * (ft_strlen(line) - s->count + 1));
	if (!newline)
		return (NULL);
	s->i = -1;
	s->j = 0;
	while (line[++(s->i)])
	{
		if (line[s->i] == -87)
			continue ;
		newline[s->j++] = line[s->i];
	}
	return (newline[s->j] = '\0', free(line), removequotes1(newline, s));
}
