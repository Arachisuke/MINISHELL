/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:23:51 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/05 11:44:10 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_var(t_all *all, char *key, char **value2)
{
	t_my_env	*tmp;

	tmp = all->my_env;
	while (tmp)
	{
		if (!strncmp(tmp->key, key, ft_strlen(key)))
			return (*value2 = tmp->value, 1);
		tmp = tmp->next;
	}
	return (0);
}
char	*findkey(char *line, int i, char *key, int flag)
{
	if (key)
	{
		free(key);
		key = NULL;
	}
	if (flag)
		i--;
	key = ft_substr(line, 0, i);
	return (key);
}
void	findvalue(char *str, char **value, char *value2)
// je lui ai envoye la str ou ya le egal..
{
	int i;

	i = 0;
	if (*value)
	{
		free(*value);
		value = NULL;
	}
	while (str[i] != '=')
		i++;
	if (str[i + 1])
		*value = ft_substr(str + (i + 1), 0, ft_strlen(str + i + 1));
	else
	{
		*value = malloc(1);
		*value[0] = '\0';
	}
	if (value2)
		*value = strjoinfree(value2, *value);
}

int	if_egal(t_all *all, char *line, char **key, char **value)
{
	int		i;
	int		flag;
	char	*value2;

	value2 = NULL;
	flag = 0;
	i = -1;
	while (line[++i])
	{
		if (!ft_isalpha(line[0]) && line[0] != '_') // check du debut
			return (msg_error(all, ERR_EGAL, line), 0);
		else if (!ft_isalnum(line[i]) && line[i] != '=' && line[i] != '_')
		{
			if (line[i] == '+' && line[i + 1] == '=')
				flag = 1;
			else
				return (msg_error(all, ERR_EGAL, line), 0);
		}
		else if (line[i] == '=')
		{
			if (i == 0)
				return (msg_error(all, ERR_EGAL, line), 0);
			*key = findkey(line, i, *key, flag);
			if (flag)
				check_var(all, *key, &value2);
			return (findvalue(line, value, value2), 1);
		}
	}
	return (0);
}

void	ft_export(t_all *all, char **strs)
{
	int		error;
	int		j;
	char	*value;
	char	*key;

	key = NULL;
	value = NULL;
	j = 0;
	while (strs[++j])
	{
		error = if_egal(all, strs[j], &key, &value);
		// key si ca se passe bien dans modif env si ca se passe mal dans le while. et en double dans le findkey
		if (!error)
			continue ;
		modify_env(key, value, all->my_env);
		if (value)
		{
			free(value);
			value = NULL;
		}
		if (key)
		{
			free(key);
			key = NULL;
		}
	}
}

char	*removequotes(char *line)
{
	int		i;
	int		count;
	char	*newline;
	int		j;

	i = -1;
	count = 0;
	newline = NULL;
	while (line[++i])
	{
		if (line[i] == -100) // supprimer les guillemets.
			count++;
	}
	if (count == 0)
		return (line);
	newline = malloc(sizeof(char) * (ft_strlen(line) - count + 1));
	if (!newline)
		return (NULL);
	i = -1;
	j = 0;
	while (line[++i])
	{
		if (line[i] == -100)
			continue ;
		newline[j++] = line[i];
	}
	newline[j] = '\0';
	free(line);
	return (newline);
}

char	*removequotes1(char *line)
{
	int		i;
	int		count;
	char	*newline;
	int		j;

	i = 0;
	count = 0;
	newline = NULL;
	while (line[i])
	{
		if (line[i] == -100 && line[i + 1] && line[i + 1] == -100)
		{
			i++;
			count = count + 2;
		}
		i++;
	}
	if (count == 0)
		return (line);
	newline = malloc(sizeof(char) * (ft_strlen(line) - count + 1));
	if (!newline)
		return (NULL);
	i = -1;
	j = 0;
	while (line[++i])
	{
		if (line[i] == -100 && line[i + 1] && line[i + 1] == -100)
		{
			i++;
			continue ;
		}
		newline[j++] = line[i];
	}
	newline[j] = '\0';
	free(line);
	return (newline);
}
char	*removedollarz(char *line)
{
	int i;
	int count;
	char *newline;
	int j;

	i = -1;
	count = 0;
	newline = NULL;
	while (line[++i])
	{
		if (line[i] == -87)
			count++;
	}
	if (count == 0)
		return (removequotes1(line));
	newline = malloc(sizeof(char) * (ft_strlen(line) - count + 1));
	if (!newline)
		return (NULL);
	i = -1;
	j = 0;
	while (line[++i])
	{
		if (line[i] == -87)
			continue ;
		newline[j++] = line[i];
	}
	newline[j] = '\0';
	free(line);
	return (removequotes1(newline));
}