/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:55:41 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/18 19:00:30 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void lexer_line(char *str, char **garbage)
{
	// init les deux structure @@@@
	// tu regardes la liste de cmd @@@@
	// if null // if que des ispace @@@
	// quotes fermer ou pas @@@@@
	// tout mettre dans une double liste chainee et les flag @@@
	// >>>> @@@@
	// retokeniser >> dans la fonction donc prendre direct les deux, et le tokeniser en double_LOWER @@@@
	// automate state @@@
}

void parser_line(char *str, char **garbage, t_lexer **lexer) // struct garbage, double pointeur pour t_lexer
{
	// recuperer la liste chainee @@@
	// regrouper les commandes entre eux [t_cmds token redirec file]
	// gerer les arguments, a voir dans liste de commande "'$shell'" // savoir comment le gerer 
	// les commandes c pipex / sans pipe execve // les redirect open avec les bonnes options
	// feuille des states @@@
	 // cas speciale : premier mot qui nest pas une commande
}

void other(char *str)
{
	// faire une struct de fd pour tout close dun coup
	// expander
	// guillemet ...
	// faire la struct garbage
	// builtin
	// if une env existe pas je le met dans ma node
	// init tcmds
	// protection si la line est NULL
	// is builtin
	// proteger les fonctions quand ya pas darg ou peu darg
}

// tester mon code @@@
//celui d'andy 
// retokeniser >> dans la fonction donc prendre direct les deux, et le tokeniser en double_LOWER @@@@
