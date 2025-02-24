#include "shellsnake.h"



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
    int taille = 1;
    //initialisation du plateau
    
    char plateau[TAILLE][TAILLE];
    initPlateau(TAILLE,plateau); 

    //snake
    Tab2 tete = {TAILLE/2,TAILLE/2}; //tete
    Tab2 dir={0,0}; //direction
    Tab2 corps[TAILLE*TAILLE]={tete,tete};

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
        tete=deplacementTete(plateau,tete,dir,&surPomme);

        //queue
        
        for (int it = taille; it>0; it--){
            corps[it] =corps[it-1];// dernière partie du serpet = avant derniere partie du serpent donc décalage du tableau
        }
        corps[0] = tete;//on ajoute la tête en première position qui à été libéré par le décalage
        
        plateau[corps[1].y][corps[1].x]='o';//la deuxième partie du serpent est son corp(pas besoin de tout réecrire, car le reste du corp va suivre jusqu'à être remplacé par " " vu qu'il est déjà écrit dans le tableau)

        plateau[corps[taille].y][corps[taille].x]=' ';//on efface la dernière partie du corps du serpent sur le plateau
        

        // for (int it= 1;it<taille; it++){
        //     plateau[corps[it].y][corps[it].x]='o';//on réecrie les positions de la queue du serpent sur le plateau en o minuscule
        // }

        plateau[corps[0].y][corps[0].x]='O'; //on finit par écrire la tête en gros
        if(surPomme==1){
            creerTableauSansSerpent(plateau,cellulesVides,&tlogCellulesVides);
            placerPomme(plateau,cellulesVides,tlogCellulesVides);
            taille++;
        }
        

        //draw
        erase();
        

        affichPlateau(TAILLE,plateau);
        usleep(INTERVALLE*100000);

    }

    endwin();
    printf("votre taille finale: %d\n",taille);
    return 0;
}