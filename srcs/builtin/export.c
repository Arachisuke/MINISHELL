/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:23:51 by ankammer          #+#    #+#             */
/*   Updated: 2024/11/07 16:19:00 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*removequotes(char *line)
{
	int		i;
	int		count;
	char	*newline;
	int		j;

	i = -1;
	count = 0;
	while (line[++i])
	{
		if ((line[i] == -39 || line[i] == -34))
			count++;
	}
	if (count == 0)
		return (line);
	newline = malloc(sizeof(char) * ft_strlen(line) - count + 1);
	i = -1;
	j = 0;
	while (line[++i])
	{
		if ((line[i] == -39 || line[i] == -34))
			continue ;
		newline[j++] = line[i];
	}
	free(line);
	return (newline);
}
int	findvalue(char *str, int i, char **value)
// je lui ai envoye la str ou ya le egal..
{
	int j;

	j = ++i;
	while (str[j] && str[j] != ' ')
		j++;
	*value = ft_substr(str, i, j - i);
	return (j);
}

int	if_export(t_all *all, char *line)
{
	int		i;
	int		flag;
	char	quotes;

	i = 0;
	quotes = 0;
	while (line[i])
	{
		if ((line[i] == -39 || line[i] == -34) && !flag)
		{
			flag = 1;
			quotes = line[i];
		}
		if (ft_strncmp(line + i, "export", 6)) // exporta=ok
		{
			if (line[i + 5] && !flag)
				return (msg_error(all, ERR_EXPORT, line), 1);
			return (0);
		}
		if (line[i] == quotes && flag)
			flag = 0;
		i++;
	}
	return (1);
}

int	findkey(t_all *all, char *line, int i, char **key)
{
	int	j;

	j = --i; // export ok=ok le j vaut le k du premier ok
	while (line[i] != ' ')
		i--;
	// i vaut l'espace
	*key = ft_substr(line, i + 1, j - i);
	if (!*key)
		return (ft_final(all, NULL, ERR_MALLOC, 0));
	return (1);
}

int	if_egal(t_all *all, char *line, char **key, char **value)
{
	int	i;
	int	flag;

	flag = 0;
	i = -1;
	while (line[++i])
	{
		if (ft_isdigit(line[i]) && line[i - 1] == ' ')
		{
			msg_error(all, ERR_EGAL, line);
			flag = 1;
		}
		if (line[i] == '=')
		{
			if (line[i - 1] == ' ')
				msg_error(all, ERR_EGAL, line);
			else if (!flag)
			{
				findkey(all, line, i, key);
				i = findvalue(line, i, value);
				modify_env(*key, *value, all->my_env);
			}
		}
	}
	return (0);
}

void	ft_export(t_all *all, char **strs)
// apres avoir vu que export se porte bien on test les arg juste apres
{
	int error;
	char *value;
	char *key;
	key = NULL;
	error = if_export(all, strs[0]);
	if (error)
		return ;
	all->line = removequotes(all->line);
	error = if_egal(all, all->line, &key, &value);
	if (!error)
		return ;
}

// modify_env(, findvalue(line, value), all->my_env);
// changer la methode pour recuperer env et value car maintenant cest line
