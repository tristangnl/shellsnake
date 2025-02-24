#include "shellsnake.h"

// #include <stdio.h>



int main(void){
    //initialize screen
    WINDOW *win = initscr();

    //initialisation random
    srand(time(NULL));

    // take player input
    keypad(win, true); //active les touches spéciales(flèches)
    nodelay(win,true);//permet de lire l'entrée de l'utilisateur en permanance
    curs_set(0); //masque le curseur


    //initialisation taille
    int taille = 0;
    //initialisation du plateau
    
    char plateau[TAILLE][TAILLE];
    initPlateau(TAILLE,plateau); 

    //snake
    Tab2 tete = {TAILLE/2,TAILLE/2}; //tete
    Tab2 dir={0,0}; //direction
    Tab2 corps[TAILLE*TAILLE];

    //pomme
    int tlogCellulesVides;//initialisation
    int cellulesVides[TAILLE*TAILLE][2];
    creerTableauSansSerpent(plateau,cellulesVides,&tlogCellulesVides);

    placerPomme(plateau,cellulesVides,tlogCellulesVides);
    int surPomme=0;
    //gameloop



    affichPlateau(TAILLE,plateau);
    // while(dir.x==0 && dir.y==0){

    // }
    while(true){
        int fleche = wgetch(win);
        if (fleche == KEY_LEFT){
            if(dir.x == 1) continue;
            dir.x =-1;
            dir.y=0;
        }
        if (fleche == KEY_RIGHT){
            if(dir.x == -1) continue;
            dir.x =1;
            dir.y=0;
        }
        if (fleche == KEY_DOWN){
            if(dir.y == -1) continue;
            dir.x =0;
            dir.y=1;
        }
        if (fleche == KEY_UP){
            if(dir.y == 1) continue;
            dir.x =0;
            dir.y=-1;
        }
        if(fleche=='\e'){//echap
            break;
        }
        surPomme=0;
        tete=deplacementSerpent(plateau,tete,dir,&surPomme);
        
        //queue
        plateau[corps[taille].y][corps[taille].x]=' ';
        for (int it = taille; it>0; it--){
            corps[it] =corps[it-1];
        }
        
        corps[0] = tete;
        
        for (int it= 1;it<=taille; it++){
            plateau[corps[it].y][corps[it].x]='o';
        }
        
        if(surPomme==1){
            creerTableauSansSerpent(plateau,cellulesVides,&tlogCellulesVides);
            placerPomme(plateau,cellulesVides,tlogCellulesVides);
            taille++;
        }
        



        //draw
        erase();
        
        
        // for (int i= 0;i< taille; i++){
        //     mvaddch(corps[i].y, corps[i].x * 2, 'o');
        // }
        // mvaddch(tete.y, tete.x * 2, 'O');

        affichPlateau(TAILLE,plateau);
        usleep(INTERVALLE*100000);

    }

    endwin();
    printf("votre taille finale: %d\n",taille+1);
    return 0;
}