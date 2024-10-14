/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:23:51 by ankammer          #+#    #+#             */
/*   Updated: 2024/10/14 17:14:52 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	if_export(char *line)
{
	int		i;
	char	*tmp;
	int		flag;
	char	quotes;

	i = 0;
	tmp = line;
	quotes = 0;
	while (tmp)
	{
		if ((*tmp == -39 || *tmp == -34) && !flag)
		{
			flag = 1;
			quotes = *tmp;
		}
		if (ft_strncmp(tmp, "export", 6))
		{
			if ((tmp[6] != ' ' && !flag) || (tmp[6] != quotes && flag))
				return (0);
		}
		if (*tmp == quotes && flag)
			flag = 0;
		tmp++;
	}
	return (1); // on va export !
}

int	if_egal(t_all *all, char *line, char **key)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i])
	{
		if (line[i] == '=' && line[i - 1] == ' ')
		{
			ft_final(all, '=', ERR_EXPORT);
			break ;
		}
	}
	while (line[--i])
	{
		if ((line[i] == -34 || line[i] == -39) && !flag)
		{
			flag = 1;
		}
		if ((line[i] == -34 || line[i] == -39) && flag)
			flag = 0;
	}
	if (line[++i] && line[i] == -34 || line[i] == -39)
		return (0);
}

int	check_export(t_all *all, char *line)
// apres avoir vu que export se porte bien on test les arg juste apres
{
	int export;
	char *value;
	char *key;
	key = NULL;
	export = ifexport(all, line); // if 0 export respecte les conditions
	export = if_egal(all, line, &key);
	// 0 mais il se passe R  @@@@@// export ok = error@@@@
	// if espace dans key exemple export "ok ok"=ok 2 ERRROR
	// if 3 ok !
	value = findvalue(line);
	// prend le premier espace ou bien continue jusqua finir trouve un espace ou la fin de l'arg
	export = check_exist(all->envp, key);
	// est ce que la key existe ou pas if 1 alors je replace if 0 je rajoute a env
	if (export)
		replaceenv();
	else
		addtoenv();

	// explication le export ne doit rien avoir apres lui mise a part l'espace ou une quotes si ya eu une quotes precedemment @@@@
	// explication si il ya un = alors le mot d'avant doit etre coller. @@@@
	// prend le dernier juste avant le egal sans egal ca ne marche pas @@@@@
	// apres le egal il prend le premier si cest un espace donc espace sinon le premier mot! if guillemet logique il prend tout
	// explication ok= "" if space suivi de guillmet et que dans les guillemets ya un espace! ERROR
	// "okwdkodkwqofk  ok"=ok // si ya un space dans le NAME c cuit
	// chiffre dans la key non,
	//mais dans la value je peux avoir chiffre nombre mais pas direct apres un espace
	// alphanum pour la value alpha pour la key
}
int	check_exist(t_all *all, char *key)
// la variable existe si oui je remplace juste la valeur sinon je rajoute une ligne.
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (args[j][i]) // if space suivi de guillemet ERROR
	{
	}
	// je verifie si ya un egal y en a pas je prend le dernier args et je dis quil est     exemple =    je prend le dernier arg juste avant egal
	while (all->envp[i])
	// je prend le dernier avant le = sinon je prend le dernier tout court
	{
		if (all->envp =)
			i++;
	}
}

char	*ft_export(t_all *all, char **args)
// checker si export est separer dun espace apres sinon faut pas le faire a getfinal.
{
	int i;
	int max;
	char *tmp;
	int newline;

	newline = 1;
	check_exist(all, args);
	max = len_env(all->envp);
	free_strs(all->envp);
	all->envp = malloc(sizeof(char *) * (max + 1 + newline));
	if (!all->envp)
		return (ft_final(all, ERR_MALLOC, 1), NULL);
	i = 0;
	while (i <= max)
	{
		all->envp[i] = ft_strdup(all->envp[i]);
		i++;
	}
	while (args[i])
	{
	}
	all->envp[i++] = ;
	all->envp[i] = NULL;
	return (all->envp);
}

// ERROR msg
// "export " export1 exportp
// "export ok=ok"
// export "ok = ok" // // export "ok =ok"
// export =ok // export opopop lol ok

// VALIDE
// export "ok= ok" // export "ok= ok ok" // export ok= ok ok

// sil ya un egal alors il doit y avoir un mot avant autre que export
// export LOL= ca fais LOL=        dans env
// export LOL OKOKOK TG=  ca export TG=
// export OKOK TGB= okok
