/**
 * \file shellsnake.h
 * \brief jeu de snake pour terminal
 * \author tristan.gnl
 * \date 28/02/2025
 */

#ifndef SHELLSNAKE_H
#define SHELLSNAKE_H

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#define TAILLEX 31//minimum 9 cases au centre du cadre disponible pour le serpent
#define TAILLEY 19//deux nombres impairs pour que le serpent apparaisse au centre
#define INTERVALLE 1.3//en dixième de seconde

/**
 * @struct Tab2
 * @brief coordonnées d'une case du tableau à double entrée plateau
 */

typedef struct {
    int x;
    int y;
} Tab2;

/**
 * \brief affiche le plateau de jeu représentant l'état de la partie
 * \param[in] plateau tableau à double entrée contenant des charactères
 * \param[in] largeur largeur du plateau à afficher
 * \param[in] hauteur hauteur du plateau à afficher
 */
void affichPlateau(char **plateau,int largeur, int hauteur);

/**
 * \brief initialise le plateau avant le démarrage de la partie(contours,fond et serpent)
 * \param[out] plateau le tableau à initialiser
 * \param[in] largeur largeur du tableau à initialiser
 * \param[in] hauteur hauteur du tableau à initialiser
 */
void initPlateau(char **plateau,int largeur, int hauteur);

/**
 * \brief placer une pomme aléatoirement sur le plateau
 * \param[out] plateau tableau à double entrée du jeu
 * \param[in] largeur largeur du plateau
 * \param[in] hauteur hauteur du plateau
 * \param[in] cellulesVides tableau contenant les coordonnées disponibles pour placer une pomme
 * \param[in] tlogCellulesVides taille logique du tableau cellulesVides
 */
void placerPomme(char **plateau,int largeur, int hauteur,int cellulesVides[][2],int tlogCellulesVides);
/**
 * \brief creer un tableau contenant toutes les positions disponibles pour placer une pomme
 * \param[in] plateau tableau à double entrée du jeu
 * \param[in] largeur largeur du plateau
 * \param[in] hauteur hauteur du plateau
 * \param[out] cellulesVides tableau contenant les coordonnées disponibles pour placer une pomme
 * \param[out] tlogCellulesVides taille logique du tableau cellulesVides
 */
void creerTableauSansSerpent(char **plateau,int largeur, int hauteur,int cellulesVides[][2],int *tlogCellulesVides);

/**
 * \brief détermine les nouvelles coordonnées de la tête
 * \param[in] plateau tableau à double entrée du jeu
 * \param[in] largeur largeur du plateau de jeu
 * \param[in] hauteur hauteur du plateau de jeu
 * \param[out] tete les coordonnées de la tête du serpent
 * \param[in] dir la direction dans laquelle le joueur souhaite se diriger
 * \return les nouvelles coordonées de la tête du serpent
 */
Tab2 deplacementTete(char **plateau,int largeur, int hauteur,Tab2 tete, Tab2 dir);

/**
 * \brief met à jour la position du serpent sur le tableau plateau de jeu
 * \param[in,out] plateau tableau à double entrée du jeu
 * \param[in] largeur largeur du plateau
 * \param[in] hauteur hauteur du plateau
 * \param[in,out] corps tableau contenant les coordonnées de chaque segment du serpent et de la tete
 * \param[in] tete les coordonnées de la tête du serpent
 * \param[in] taille taille du serpent et taille logique de corps[]
 * \param[in] dir la direction dans laquelle le joueur souhaite se diriger
 */
void majPlateau(char **plateau,int largeur, int hauteur,Tab2 corps[],Tab2 tete,int taille,Tab2 dir);

/**
 * \brief vérifie si la tête est en collision avec un mur, sa queue ou une pomme
 * \param[in] plateau tableau à double entrée du jeu
 * \param[in] largeur largeur du plateau de jeu
 * \param[in] hauteur hauteur du plateau de jeu
 * \param[in] tete les coordonnées de la tête du serpent
 * \param[out] surPomme égal à 1 si le serpent est sur une pomme 0 sinon
 * \param[out] collision égal à 1 si le serpent est sur sa queue ou un mur 0 sinon
 */
void testCollisions(char **plateau,int largeur, int hauteur,Tab2 tete,int *surPomme,int *collision);

/**
 * \brief lance une partie de snake
 * \param[in] hauteur hauteur du plateau
 * \param[in] largeur largeur du plateau
 * \param[in] vitesse intervalle entre chaque affichage du plateau
 * \param[in] nbPommes le nombre de pommes à positionner sur le plateau
 * \return le score final du joueur
*/
int lancerPartie(int largeur, int hauteur,float vitesse,int nbPommes);

/**
 * \brief alloue le plateau de jeu sur le tas
 * \param[in] hauteur hauteur du plateau à allouer
 * \param[in] largeur largeur du plateau à allouer
 * \return le plateau de jeu alloué
*/
char** allouerPlateau(int hauteur, int largeur);
/**
 * \brief libère le plateau de jeu alloué en début de partie
 * \param[in] plateau le tableau à libérer
 * \param[in] hauteur hauteur du plateau à libérer
 */
void libererPlateau(char** plateau, int hauteur);

/**
 * \brief affiche le Menu du jeu
 * \param[in] win1 fenêtre principale du menu
 * \param[in] win2 fenêtre secondaire du menu
 * \param[in] colorTab tableau des options de couleur
 * \param[in] sizeTab tableau des options de taille
 * \param[in] speedTab tableau des options de vitesse
 * \param[in] pos position verticale du curseur du joueur sur le menu
 * \param[in] itSize itérateur sur l'indice du sizeTab
 * \param[in] itSpeed itérateur sur l'indice du speedTab
 * \param[in] itColor itérateur sur l'indice du colorTab
 * \param[in] nbPommes nombre de pommes choisi
 * \param[in] score score du joueur de la dernière partie
 */
void afficheMenu(WINDOW *win1,WINDOW *win2,char colorTab[][10],char sizeTab[][10],char speedTab[][10],int pos,int itSize,int itSpeed,int itColor,int nbPommes,int score);

/**
 * \brief menu du jeu qui permet de parametrer sa partie
 */
void menu(void);

/**
 * \brief affiche des sous fenêtres pour que le joueur choisisse ses préférences
 * \param[in] tailleCustom vrai si le joueur à choisi de customiser la taille du plateau, faux sinon
 * \param[in] vitesseCustom vrai si le joueur à choisi de customiser la vitesse du jeu, faux sinon
 * \param[in,out] largeur largeur du plateau
 * \param[in,out] hauteur hauteur du plateau
 * \param[in,out] vitesse intervalle entre chaque affichage du plateau
 * \param[in] itColor itérateur sur l'indice du colorTab pour connaître la couleur à afficher
 * \return vrai si l'utilisateur à voulu quitter cette fenêtre, faux sinon
 */
int customMenuSize(int tailleCustom,int vitesseCustom,int *largeur,int *hauteur,float *vitesse,int itColor);


#endif //SHELLSNAKE_H