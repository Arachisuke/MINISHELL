/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:23:51 by ankammer          #+#    #+#             */
/*   Updated: 2024/11/05 16:16:30 by wzeraig          ###   ########.fr       */
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
		*value = NULL;
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

int	if_egal(t_all *all, char **strs, char **key)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (strs[j])
	{
		while (strs[j][i])
		{
			if (strs[j][i] == '=')
			{
				if (i == 0)
					return (msg_error(all, ERR_EGAL, strs[j]), 0);
				// juste renvoyer une erreur, le = est avec espace.
				return (*key = ft_substr(strs[j], 0, i), j);
			}
			i++;
		}
		i = 0;
		j++;
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
	error = if_egal(all, strs, &key);
	if (!error) // return 0 en error
		return ;
	findvalue(strs[error], &value);
	ft_env(all->my_env);
	modify_env(key, value, all->my_env);
	ft_env(all->my_env);
}
