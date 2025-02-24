#include "shellsnake.h"

// #include <stdio.h>

// Tab2 segments[256];

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

    //pomme
    int tlogCellulesVides;//initialisation
    int cellulesVides[TAILLE*TAILLE][2];
    creerTableauSansSerpent(plateau,cellulesVides,&tlogCellulesVides);

    placerPomme(plateau,cellulesVides,tlogCellulesVides);
    int surPomme=0;
    //gameloop



    affichPlateau(TAILLE,plateau);

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
        if(surPomme==1){
            creerTableauSansSerpent(plateau,cellulesVides,&tlogCellulesVides);
            placerPomme(plateau,cellulesVides,tlogCellulesVides);
            taille++;
        }
        
        //queue
        // for (int i = taille; i>0; i--){
        //     segments[i] =segments[i-1];
        // }

        // segments[0] = tete;

        // tete.x += dir.x;
        // tete.y += dir.y;

        // if(tete.x == pomme.x && tete.y ==pomme.y){
        //     taille=taille+1;

        //     pomme.x = rand() % TAILLE;
        //     pomme.y = rand() % TAILLE;
        // }

        //placer pomme
        // if(tete == '@'){
        //     taille=taille+1;
        //     creerTableauSansSerpent(plateau,cellulesVides,&tlogCellulesVides);
        // placerPomme(plateau,cellulesVides,tlogCellulesVides);
        // }
        // creerTableauSansSerpent(plateau,cellulesVides,&tlogCellulesVides);
        // placerPomme(plateau,cellulesVides,tlogCellulesVides);

        //draw
        erase();
        
        // mvaddch(pomme.y,pomme.x * 2,'@');
        
        // for (int i= 0;i< taille; i++){
        //     mvaddch(segments[i].y, segments[i].x * 2, 'o');
        // }
        // mvaddch(tete.y, tete.x * 2, 'O');

        affichPlateau(TAILLE,plateau);
        usleep(200000);

    }

    endwin();
    printf("votre score: %d\n",taille);
    return 0;
}