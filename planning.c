/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:55:41 by wzeraig           #+#    #+#             */
/*   Updated: 2024/12/03 14:43:46 by wzeraig          ###   ########.fr       */
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
// gerer dans sort cmds, << heredoc,
	// dire que c un limiteur le caractere dapres...
// tester le heredoc que jai fais

// gerer dans sortcmds les expands....

// historique @@@@
// cree une structure VOIR MAIN @@@

//< in1 << in2 cat >out1 >out2 -e  >out3 >out4 -er | >  -l out4 cd -l  >out4 -l
// verifier le com qui est dans sort_cmds @@@@

//<< lim1 < <<lim 2 || << lim3 < infile1 << lim4

// faire un malloc de fd comme ca... si ya plusieurs je les ouvre tous avec differnet int fd comme ca jai le cheminn de tous,
	// dans l'exec je prendrais le dernier mais comme ca jai ouvert tout les fd jai ecris dedans jai juste a savoir via lexec si cest le dernier lui il va juste parcourir jusqua la fin la node redir...
// je le return dans node... depuis la fonction comme ca le retour de la fonction sers quaux erreur.. parfait

// expander regrouper les info sur les quotes, et commencer lexpand
// @ANDY fais la fonction malloc et copie des ENV et rend line tout beau tout propre.
// VERIFIER EXPAND EN L'AFFICHANT YA UN PB
//<$HOME $'HOME' '$HOME' '$'HOME "$HOME" "$""HOME" $$HOME

// faire le tour de toute les fonctions gerer les erreur si ya une erreur free,
	// ect ect...entre chaque cmd ca free.\


// ERROR_REDIR a verifi gdb @@@@

// AUJOURDHUI 1 octobre
// verifier le quotes
// et un quotes fermer cest une chaine! un arguments
// de changer les returns et surtout dans state init.
// tester par quelquun
// builtin

// changer les returns,
	// par l'erreur qui correspond ainsi que la fonction qui correspond.
// la fonction qui free tout,
	// et gerer le parsing relire chaque moment et faire la bonne redirection false
	// -> free, true ->continue
// tester le here_doc en profondeur et le expander.
// younes ou autre.
// builtin
// exec
// signaux
// lire les fonctionnalite a apoorte sur medium
// corriger les fautes!

// test echo  "ah euh ah euh" -n , -n n'est pas pris en compte comme option

// 2 octobre
// changer tout les return(0) par success// return(1) par le define correspondant
// changer apres le final enlever le retour car final return deja
// revoir la fonction ligne par ligne si tout se rejoins que ce soit au niveau des erreurs etc
// split le terminator
// tester par quelqun
// NEWNEW $? ou $variableinexistante marche pas

// TEST a gerer
// "" juste ca faut le parse,
	// donc pas de verif dans parse_line le parser et lenvoyer a l'exec
// $variable inexistante il peut ne pas y avoir de line donc est ce que la protection serait pas utile finalement
// $?
// echo "" que mettre a l'interieur des guillemets ? si cest espace cest deja fait

// verifier chaque etape et sil faut verifier line en debut de fonction car ya des fonctions qui la change tel que get_final

// $HME
// \0 -> mallocinput ->strs ft_final free, continue
// $?
// ""
// plus besoin de faire *-1

//  < "Makefile" "<<oui'" echo "'"$HOME"'" a gerer @@@@
// < "Makefile" "<<oui'" echo "'"$HOME"'" @@@@
//<<oui'@@@
//"ok ok" "123ok" "132ok" "<<ook" "|" @@@@
// echo "'l'" > '"lo"'

// THEME A GERER
// EXPANDEER
// QUOTES
// SAVOIR PARSER LES COMMANDE
// LES TOKENS

// faire tout les test du repertoire de commande
// gerer chaque erreur avec le bon message
// cas envoyez juste : ou ! ca ne renvoie rien car ni un token(> ou |) ni un string donc rien par contre envoyez deux fois lun de ses caractere command not found
// yann a pas gerer il a dis direct command not found car cest une string! if pas redir donc cest une commande donc erreur!
// > gerer car le msg parle de ce quil ya apres donc si cest juste > alors dire newline sinon > | ou >>> ca va parler de pipe ou de redir

// TESTER
// $USER_
// double dollar ??
// sil ya un pipe ca ne marchait pas ...le probleme de l'incrementation de J....
// reregler ""ls (marche) a "" ls (cmd not found)

// OCTOBRE 13!

// le *-1 des quotes ne sers a rien!
// valgrind $ nombre impair
// valgrind // echo "$HOME:$=" // echo $: @@@@@
// mettre plein de commande et ensuite exit et/ou mettre juste un caratere @@@
// tester $$HOME si home est bien expand @@@
// tester $$$HOME @@@
// erreur $$HOME$HOME @@@@
// valgrind tout les test au dessus en plus de ceux repertorier sur le googlesheet
// makefile le minishell.a et minishell ne se supp pas a verifier
// supp les fonctions negative hollow et double dollar et chercher els fonctions inutiliser @@@
// tester avec guillemet les token et sans guillemet mettre des redir des pipe ect,
	// et mettre des vrai sans guillemet tjr regarde si count vaut bien le count et lentotal et bon!
// verifier si cest vraiment le pid du shell le $$ et pas celui dun prog
// verifier si ont doit utiliser toute les fonctions proposer..
// strerror est interessant pour les msg derreur avec errno
// si un expand existe pas error chez yan et si ya echo > $HOE il dit que c une erreur alors que dans bash ca affiche juste rien
	// nous c boon
// supp syntax error line
// doit on supp lhistorique ?

// 14 octobre
// je fais unset et export andy exit et cd
// on verifie bien les bultins sils sont correct
// balancer le pipex // plus sortie d'erreur
// balancer les signaux
// faire full test avec valgrind
// rajoute les messages d'erreur de CHAQUE BULTINS et NOUVELLE FONCTIONS
// chaque fonction rajouter,
	// bien free les valeurs et mettre NUL au copie de valeur et bien renvoyez le bon msg
// changer toutes les fonctions qui depend de env car env est devenu une liste chaine @@@@@

// faire node de env@@
// faire export avec cmds au lieu de line c'est plus simple.

// 5 NOVEMBRE
// verifier export avec gdb et toutiquenti
// finir export unset et poser pipex AUJOURDHUI
// ensuite finir par tout tester.

// 6 NOV
// paufiner le msgerror,
	// et remettre tout le code a jour avec cette fonction. @@@@@@@@@@
// verifier les cas d'erreur de export @@@@@@
// verifier unset par rapport au index de env,
	// jai deja mis un printf pour verifier lavant et apres changement@@@@@@@@@

// cas d'erreur de unset... juste la cmd doit etre bien ortographier c tout @@@@
// export plusieurs variable en meme temps @@@@@
// si le premier unset existe pas ou le premier export nexiste pas est ce que ceux dapres qui existe marche @@@@
// le cas chiffre espace chiffre -> erreur et on intialise la variable @@@
// si la cmd est mauvaise c pipex qui gere @@@@

// changer la methode pour recuperer env et value car maintenant cest line
// DERNIERE VERIF CAS D'ERREUR EXPORT UNSET
// entre quotes pas d'espace.

// echo
// all my env faut le free apres la boucle vu quon en a besoin pendant toute lexecution!@@@@@@
// rechercher tout les malloc et les sorties d'erreur et gerer en faisant des free et des vrai sortie et msg
// regler et revoir tout les builtins et cas d'errreur builtin
// lire le main tres lentement...valgrind et entre fonction reaction en chaine.
//

// pourquoi quand ya une guillemet on dis que cest un autre mot.
// unclosed quotes sa segfault @@@@@
// revenir a mon ancien export et le retester.

// 9 NOV

// finir parse_line ce quil ya sur ton livre, et remettre lancien export

// lancien raisonnement de notre parse line cetait que quand yavais une commande comme echo "" on pensait quil comprennais espace,
	// mais il comprennait que cetait vide,
	// y avais les deux cas je les avait repetorier]

// a quoi sers la sortie de ft_final
// reduire export et les autres fonction a 25
// PIPEX
// test avec l'ecran split
// printf count, line, et cmds.->

// execve(data->path, data->cmd, envp); // le path de la commande la commande, et l'env
// data.id -> le pid du process
// pipefd, le double fd qui permet la communication entre les process.
// here_doc envoyez le fd direct.

// 14 nov
// PIPEX
// faire le test du exit
// faire le test de combine plusieurs commande
// et apres faire full test avec valgrind.

// une commande exit @@@@@@
// les builtins @@@@
// one command, ft_errchild pour free ??

// une commande, et ensuite exit ca n'exit pas du premier coup @@@@
// deux commande une qui existe pas sa seg @@@@@

// gerer le onecmd free et seg
// gerer builtins.
// plusieurs commande qui existe ou non 
// le nom du fichier outfile s'ouvre en double





// 20 nov
// erreur avec et sans break se concentrer sur free_all errchild errparent



// changement principaux pour les leaks, pipe.pid, javais free2child, mais je lavais deja vu et je lavais change.
// le deuxieme changement c'etait que cmds.strs avait un malloc.
// troisieme changement le plus interessant et important peut etre, le ft_final dans errchild, le child partage toute les ressources de son pere, donc meme les ressources de tout le minishell logique.
// free_env ....

// demande une explication pour ft_final car finalement c'est pas si logique
// vu que le parent quoi quil arrive il va supprimer ca.



// test free_env avec gdb.


// bazaluga mas dis quil faut tout free ssans distinction dans lenfant ca veut dire que notre erreur venait dautre part.




// donc quand tu exit tu dois tout free.
// free all, free env , et meme errchild.
// enfant il free all, free env, et errchild
// parent il free all free env et errparent
// si ya un exit, tu fais la total de l'enfant ou du parent.
echo $UIDt le pipex.path, si il ya le exit...
// donc dans le exit autant mettre le errchild a la place du VRAI exit donc dans le ft_exit on change pas errchld qui a la vrai fonction exit en elle donc elle free et apres exit, ca ne change rien.
// dans exit je met errchild qui lui a deja free env et ft_final, et free de la session pipex
// errparent necessite que de free la session pipex car il exit pas donc il va se faire free dans le main apres.
// errchild exit donc il doit tout free avant de quitter sauf sil execve, donc un errchild qui dedans a free env free final et la session en cours puis il exit.
// cest pour ca que jai remplace les exit de isbuiltin et de exit en lui meme pas errchild car il a deja tout errchild.

// // exit | ls | echo -n | cd
// ce test represente quelque erreur rien de grave.


// en terme de nouveaute enormement de supp de fonction et de ligne dans certaines fonctions.
// reglage de echo et de cd.
// tout les leaks





// cd et echo et plein de details regler.
// <<<<<<<<< mauvais calcul de malloc. car deux sameredir valent 1, donc 3 sameredir vaut 2. 4 sameredir vaut 2.
// <<><>>< free(invalidepointeur) @@@@@@@
// check aussi si le count est bon car dans ce cas il est surement pas bon car un cas similaire ne l'etais pas. @@@@@@
// reparer checkquotes andredir et double redir. @@@@@@@@


// valgrind.
// le bon output
// le bon message d'erreur
// $?
// SIGNAUX
// attendre andy pour le cd, et les messages d'erreurs




// $?@@@@
// cd @@@@
// signaux@@@@

// $? @@@@
// gerer all.exitcode. @@@@


//"<< $""$hola""$$""b""" @@@@@@@@@
// tab fill tab crois que cest un token@@@@
// activer les signaux et tester
//input csv pas complet @@@@@






// verifier le env -i avec jules
// test de leak.
// test de output.
// test de code d'erreur
// test de message d'erreur
// reduire les lignes.
// export ""| -> count = 3 
// heredoc signaux