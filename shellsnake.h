#ifndef SHELLSNAKE_H
#define SHELLSNAKE_H

#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define TAILLEX 31//35//minimum 9 cases au centre du cadre disponible pour le serpent
#define TAILLEY 19
#define INTERVALLE 1.3//en dixième de seconde

typedef struct {
    int x;
    int y;
} Tab2;

void affichPlateau(char plateau[][TAILLEX]);
void initPlateau(char plateau[][TAILLEX]);
void placerPomme(char plateau[][TAILLEX],int cellulesVides[][2],int tlogCellulesVides);
void creerTableauSansSerpent(char plateau[][TAILLEX],int cellulesVides[][2],int *tlogCellulesVides);
Tab2 deplacementTete(char plateau[][TAILLEX],Tab2 tete, Tab2 dir);
void testCollisions(char plateau[][TAILLEX],Tab2 tete,int *surPomme,int *collision);


#endif //SHELLSNAKE_H