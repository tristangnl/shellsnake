/**
 * \file shellsnake.h
 * \brief jeu de snake
 * \author tristan.gnl
 * \date 28/02/2025
 */

#ifndef SHELLSNAKE_H
#define SHELLSNAKE_H

#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
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
 */
void affichPlateau(char **plateau,int largeur, int hauteur);

/**
 * \brief initialise le plateau avant le démarrage de la partie(contours,fond et serpent)
 * \param[out] plateau le tableau à initialiser
 */
void initPlateau(char **plateau,int largeur, int hauteur);

/**
 * \brief placer une pomme aléatoirement sur le plateau
 * \param[out] plateau tableau à double entrée du jeu
 * \param[in] cellulesVides tableau contenant les coordonnées disponibles pour placer une pomme
 * \param[in] tlogCellulesVides taille logique du tableau cellulesVides
 */
void placerPomme(char **plateau,int largeur, int hauteur,int cellulesVides[][2],int tlogCellulesVides);
/**
 * \brief creer un tableau de toutes les positions disponibles pour placer une pomme
 * \param[in] plateau tableau à double entrée du jeu
 * \param[out] cellulesVides tableau contenant les coordonnées disponibles pour placer une pomme
 * \param[out] tlogCellulesVides taille logique du tableau cellulesVides
 */
void creerTableauSansSerpent(char **plateau,int largeur, int hauteur,int cellulesVides[][2],int *tlogCellulesVides);

/**
 * \brief détermine les nouvelles coordonnées de la tête
 * \param[in] plateau tableau à double entrée du jeu
 * \param[out] tete les coordonnées de la tête du serpent
 * \param[in] dir la direction dans laquelle le joueur souhaite se diriger
 * \return les nouvelles coordonées de la tête du serpent
 */
Tab2 deplacementTete(char **plateau,int largeur, int hauteur,Tab2 tete, Tab2 dir);

/**
 * \brief met à jour la position du serpent sur le tableau plateau
 * \param[in,out] plateau tableau à double entrée du jeu
 * \param[in,out] corps tableau contenant les coordonnées de chaque segment du serpent et de la tete
 * \param[in] tete les coordonnées de la tête du serpent
 * \param[in] taille taille du serpent et taille logique de corps[]
 * \param[in] dir la direction dans laquelle le joueur souhaite se diriger
 */
void majPlateau(char **plateau,int largeur, int hauteur,Tab2 corps[],Tab2 tete,int taille,Tab2 dir);

/**
 * \brief vérifie si la tête est en collision avec un mur, sa queue ou une pomme
 * \param[in] plateau tableau à double entrée du jeu
 * \param[in] tete les coordonnées de la tête du serpent
 * \param[out] surPomme égal à 1 si le serpent est sur une pomme 0 sinon
 * \param[out] collision égal à 1 si le serpent est sur sa queue ou un mur 0 sinon
 */
void testCollisions(char **plateau,int largeur, int hauteur,Tab2 tete,int *surPomme,int *collision);

int lancerPartie(int largeur, int hauteur,int vitesse);

char** allouerPlateau(int hauteur, int largeur);

void libererPlateau(char** plateau, int hauteur);





#endif //SHELLSNAKE_H