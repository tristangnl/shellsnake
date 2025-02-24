#include "shellsnake.h"


void initPlateau(int tlog,char plateau[][TAILLE]){
    int i,j;
    for (i=0;i<tlog;i++){
        for (j=0;j<tlog;j++){
            if(i==0 || i==TAILLE-1 || j==0 || j==TAILLE-1) plateau[i][j]='X';
            else if(i==TAILLE/2 && j==TAILLE/2) plateau[TAILLE/2][TAILLE/2]='O';
            else plateau[i][j]=' ';
        }
    }
}


void affichPlateau(int tlog,char plateau[][TAILLE]){
    int i,j;
    printw("\n\t");
    for (i=0;i<tlog;i++){
        for (j=0;j<tlog;j++){
            printw("%c  ", plateau[i][j]);
        }
        printw("\n");
        printw("\t");
    }
    printw("\n");
}

void creerTableauSansSerpent(char plateau[][TAILLE],int cellulesVides[][2],int *tlogCellulesVides){
    int i,j;
    *tlogCellulesVides=0;
    for (i=1;i<TAILLE-1;i++){
        for(j=1;j<TAILLE-1;j++){
            if(plateau[i][j]=='O' || plateau[i][j]=='o'){
                continue;
            }
            else{
                cellulesVides[*tlogCellulesVides][0]=i;
                cellulesVides[*tlogCellulesVides][1]=j;
                (*tlogCellulesVides)++;
            }
        }
    }
    // if(*tlogCellulesVides==0){
    //     printw('erreur: plus de place sur le plateau, vous avez gagnez');//lancer exception?
    // }
}

void placerPomme(char plateau[][TAILLE],int cellulesVides[][2],int tlogCellulesVides){
    int x,y,aleatoire;
    if(tlogCellulesVides==0){
        printw("erreur: plus de place sur le plateau, vous avez gagnez"); //lancer exception?
    }
    aleatoire=rand() % tlogCellulesVides;//entre 0 et tlogCellulesVides[inclus]

    x=cellulesVides[aleatoire][0];
    y=cellulesVides[aleatoire][1];
    plateau[x][y]='@';
}

Tab2 deplacementSerpent(char plateau[][TAILLE],Tab2 tete, Tab2 dir,int *surPomme){
    if(dir.x==1 && dir.y==0){//droite
        plateau[tete.y][tete.x]=' ';
        tete.x++;
        if(plateau[tete.y][tete.x]=='@'){
            *surPomme=1;
        }
        plateau[tete.y][tete.x]='O';
    }
    else if(dir.x==-1 && dir.y==0){//gauche
        plateau[tete.y][tete.x]=' ';
        tete.x--;
        if(plateau[tete.y][tete.x]=='@'){
            *surPomme=1;
        }
        plateau[tete.y][tete.x]='O';
    }
    else if(dir.x==0 && dir.y==-1){//haut
        plateau[tete.y][tete.x]=' ';
        tete.y--;
        if(plateau[tete.y][tete.x]=='@'){
            *surPomme=1;
        }
        plateau[tete.y][tete.x]='O';
    }
    else if(dir.x==0 && dir.y==1){//bas
        plateau[tete.y][tete.x]=' ';
        tete.y++;
        if(plateau[tete.y][tete.x]=='@'){
            *surPomme=1;
        }
        plateau[tete.y][tete.x]='O';
    }
    return tete;
}



//     int fleche = wgetch(win);
//     if (fleche == KEY_LEFT){
//         if(dir.x == 1) return;
//         dir.x =-1;
//         dir.y=0;
//     }
//     if (fleche == KEY_RIGHT){
//         if(dir.x == -1) return;
//         dir.x =1;
//         dir.y=0;
//     }
//     if (fleche == KEY_DOWN){
//         if(dir.y == -1) return;
//         dir.x =0;
//         dir.y=1;
//     }
//     if (fleche == KEY_UP){
//         if(dir.y == 1) return;
//         dir.x =0;
//         dir.y=-1;
//     }
//     if(fleche=='\e'){//echap
//         break;
//     }
// }



// bool testCollisionPomme(){

// }

// bool testCollisionMurEtQueue(){

// }