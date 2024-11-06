/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:23:51 by ankammer          #+#    #+#             */
/*   Updated: 2024/11/06 13:00:35 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	findvalue(char *str, char **value)
// je lui ai envoye la str ou ya le egal..
{
	int i;

	i = 0;
	while (str[i] != '=')
		i++;
	if (str[i + 1])
		*value = ft_substr(str + (i + 1), 0, ft_strlen(str + i + 1));
	else
	{
		*value = malloc(1);
		*value[0] = '\0';
	}
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
				return (msg_error(all, ERR_EXPORT, line), 1); // a changer
			return (0);
		}
		if (line[i] == quotes && flag)
			flag = 0;
		i++;
	}
	return (1);
}

int	if_egal(t_all *all, char *strs, char **key, char **value)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		if (ft_isdigit(strs[i]))
			msg_error(all, ERR_EGAL, strs);
		if (strs[i] == '=')
		{
			if (i == 0)
				return (msg_error(all, ERR_EGAL, strs), 0);
			return (*key = ft_substr(strs, 0, i), findvalue(strs, value), 1);
		}
		i++;
	}
	return (0);
}

void	ft_export(t_all *all, char **strs)
// apres avoir vu que export se porte bien on test les arg juste apres
{
	int error;
	int j;
	char *value;
	char *key;
	key = NULL;
	j = 1;
	error = if_export(all, strs[0]);
	if (error)
		return ;
	while (strs[j])
	{
		error = if_egal(all, strs[j], &key, &value);
		if (!error)
		{
			j++;
			continue ;
		}
		modify_env(key, value, all->my_env);
		j++;
	}
	ft_env(all->my_env);
}
