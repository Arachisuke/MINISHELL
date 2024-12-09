/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:23:51 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/09 14:50:22 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_var(t_all *all, char *key, char **value2, int flag)
{
	t_my_env	*tmp;

	if (!flag)
		return (0);
	tmp = all->my_env;
	while (tmp)
	{
		if (!strncmp(tmp->key, key, ft_strlen(key)))
			return (*value2 = tmp->value, 1);
		tmp = tmp->next;
	}
	return (0);
}

char	*findkey(char *line, int i, char **key, int flag)
{
	if (i == 0)
		return (NULL);
	if (key && *key)
	{
		free(*key);
		*key = NULL;
	}
	if (flag)
		i--;
	*key = ft_substr(line, 0, i);
	return (*key);
}

void	findvalue(char *str, char **value, char *value2)
{
	int	i;

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
	all->utils->value2 = NULL;
	all->utils->flag = 0;
	all->utils->i = -1;
	while (line[++all->utils->i])
	{
		if (!ft_isalpha(line[0]) && line[0] != '_')
			return (msg_error(all, ERR_EGAL, line), 0);
		else if (!ft_isalnum(line[all->utils->i]) && line[all->utils->i] != '='
			&& line[all->utils->i] != '_')
		{
			if (line[all->utils->i] == '+' && line[all->utils->i + 1] == '=')
				all->utils->flag = 1;
			else
				return (msg_error(all, ERR_EGAL, line), 0);
		}
		else if (line[all->utils->i] == '=')
		{
			if (!findkey(line, all->utils->i, key, all->utils->flag))
				return (msg_error(all, ERR_EGAL, line), 0);
			return (check_var(all, *key, &all->utils->value2, all->utils->flag),
				findvalue(line, value, all->utils->value2), 1);
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
