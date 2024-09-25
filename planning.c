/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:55:41 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/25 17:43:18 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_line(char *str, char **garbage)
{
	// init les deux structure @@@@
	// tu regardes la liste de cmd @@@@
	// if null // if que des ispace @@@
	// quotes fermer ou pas @@@@@
	// tout mettre dans une double liste chainee et les flag @@@
	// >>>> @@@@
	// retokeniser >> dans la fonction donc prendre direct les deux
	// automate state @@@
}

void	parser_line(char *str, char **garbage, t_lexer **lexer)
// struct garbage, double pointeur pour t_lexer
{
	// recuperer la liste chainee @@@
	// regrouper les commandes entre eux [t_cmds token redirec file] @@@
	// les redirect open avec les bonnes options @@@@
 	// feuille des states @@@
	// tester mon code @@@
	// celui d'andy @@@
	// init tcmds @@@@
	// protection si la line est NULL @@@
	// is builtin @@@@
	// retokeniser >> dans la fonction donc prendre direct les deux @@@
}

void	other(char *str)
{
	// proteger les mallocs @@@@
	// expander 
	// guillemet ...
	// gerer les arguments, a voir dans liste de commande "'$shell'"
	// if une env existe pas je le met pas dans ma node
	// faire la struct garbage
	// builtin
	// les code d'exit et free garbage close struct fd
	// cas speciale : premier mot qui nest pas une commande
	// regrouper DLOWER LOWER GREATER DGREATER
}
// gerer dans sort cmds, << heredoc, dire que c un limiteur le caractere dapres...
// tester le heredoc que jai fais

// gerer dans sortcmds les expands....


// historique @@@@
// cree une structure VOIR MAIN @@@


//< in1 << in2 cat >out1 >out2 -e  >out3 >out4 -er | >  -l out4 cd -l  >out4 -l 
// verifier le com qui est dans sort_cmds @@@@



//<< lim1 < <<lim 2 || << lim3 < infile1 << lim4

// faire un malloc de fd comme ca... si ya plusieurs je les ouvre tous avec differnet int fd comme ca jai le cheminn de tous, dans l'exec je prendrais le dernier mais comme ca jai ouvert tout les fd jai ecris dedans jai juste a savoir via lexec si cest le dernier lui il va juste parcourir jusqua la fin la node redir...
// je le return dans node... depuis la fonction comme ca le retour de la fonction sers quaux erreur.. parfait


// expander regrouper les info sur les quotes, et commencer lexpand

// @ANDY fais la fonction malloc et copie des ENV et rend line tout beau tout propre.
// faire le tour de toute les fonctions gerer les erreur si ya une erreur free, ect ect...entre chaque cmd ca free.



// VERIFIER EXPAND EN L'AFFICHANT YA UN PB