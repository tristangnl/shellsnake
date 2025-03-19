#include "shellsnake.h"


void initPlateau(char **plateau,int largeur, int hauteur){
    int i,j;
    for (i=0;i<hauteur;i++){
        for (j=0;j<largeur;j++){
            if(i==0 || i==hauteur-1 || j==0 || j==largeur-1) plateau[i][j]='X';
            else if(i==hauteur/2 && j==largeur/2) plateau[hauteur/2][largeur/2]='^';
            else plateau[i][j]=' ';
        }
    }
}


void affichPlateau(char **plateau,int largeur, int hauteur){
    int i,j;
    printw("\n\t");
    for (i=0;i<hauteur;i++){
        for (j=0;j<largeur;j++){
            printw("%c ", plateau[i][j]);
        }
        printw("\n");
        printw("\t");
    }
    printw("\n");
}

void creerTableauSansSerpent(char **plateau,int largeur, int hauteur,int cellulesVides[][2],int *tlogCellulesVides){
    int i,j;
    *tlogCellulesVides=0;
    for (i=1;i<hauteur-1;i++){
        for(j=1;j<largeur-1;j++){
            if(plateau[i][j]=='<' || plateau[i][j]=='>' || plateau[i][j]=='^' || plateau[i][j]=='v' || plateau[i][j]=='o'||plateau[i][j]=='@'){
                continue;
            }
            else{
                cellulesVides[*tlogCellulesVides][0]=i;
                cellulesVides[*tlogCellulesVides][1]=j;
                (*tlogCellulesVides)++;
            }
        }
    }
}

void placerPomme(char **plateau,int largeur, int hauteur,int cellulesVides[][2],int tlogCellulesVides){
    int x,y,aleatoire;
    aleatoire=rand() % tlogCellulesVides;//entre 0 et tlogCellulesVides[inclus]

    x=cellulesVides[aleatoire][0];
    y=cellulesVides[aleatoire][1];
    plateau[x][y]='@';
}

Tab2 deplacementTete(char **plateau,int largeur, int hauteur,Tab2 tete, Tab2 dir){
    if(dir.x==1 && dir.y==0){//droite
        (tete.x)++;
    }
    else if(dir.x==-1 && dir.y==0){//gauche
        (tete.x)--;
    }
    else if(dir.x==0 && dir.y==-1){//haut
        (tete.y)--;
    }
    else if(dir.x==0 && dir.y==1){//bas
        (tete.y)++;
    }
    return tete;
}


void majPlateau(char **plateau,int largeur, int hauteur,Tab2 corps[],Tab2 tete,int taille,Tab2 dir){
    //corps        
    for (int it = taille; it>0; it--){
        corps[it] =corps[it-1];// dernière partie du serpent = avant derniere partie du serpent donc décalage du tableau
    }
    corps[0] = tete;//on ajoute la tête en première position qui a été libéré par le décalage
    
    plateau[corps[1].y][corps[1].x]='o';//la deuxième partie du serpent est son corps(pas besoin de tout réecrire, car le reste du corp va suivre jusqu'à être remplacé par " " vu qu'il est déjà écrit dans le tableau)
    if(plateau[corps[taille].y][corps[taille].x]!='@'){
        plateau[corps[taille].y][corps[taille].x]=' ';//on efface la dernière partie du corps du serpent sur le plateau sauf si une pomme est apparue par dessus entre temps
    }
    
    //tete
    if(dir.x==1 && dir.y==0){
        plateau[corps[0].y][corps[0].x]='>';
    }
    else if(dir.x==-1 && dir.y==0){
        plateau[corps[0].y][corps[0].x]='<';

    }
    else if(dir.x==0 && dir.y==1){
        plateau[corps[0].y][corps[0].x]='v';
    }
    else{
        plateau[corps[0].y][corps[0].x]='^';
    }
    //on finit par écrire la tête sur la nouvelle position du tableau
}

void testCollisions(char **plateau,int largeur, int hauteur,Tab2 tete,int *surPomme,int *collision){
        if(plateau[tete.y][tete.x]=='@'){
            *surPomme=1;
            return;
        }
        if(plateau[tete.y][tete.x]=='X'||plateau[tete.y][tete.x]=='o'){
            *collision=1;
            return;
        }
}


char** allouerPlateau(int hauteur, int largeur) {
    char** plateau = (char**)malloc(hauteur * sizeof(char*));
    if (plateau == NULL) {
        printf("Échec de l'allocation mémoire\n");
        exit(1);
    }
    for (int i = 0; i < hauteur; i++) {
        plateau[i] = (char*)malloc(largeur * sizeof(char));
        if (plateau[i] == NULL) {
            for (int ifree = 0; ifree < i; ifree++) {
                free(plateau[ifree]);
            }
            free(plateau);
            printf("Échec de l'allocation mémoire\n");
            exit(1);
        }
    }
    return plateau;
}

void libererPlateau(char** plateau, int hauteur) {
    for (int i = 0; i < hauteur; i++) {
        free(plateau[i]);
    }
    free(plateau);
}