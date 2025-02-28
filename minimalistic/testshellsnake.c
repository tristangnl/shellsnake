#include "shellsnake.h"

int main(void){
    //initialisation fenêtre(ncurses)
    WINDOW *win = initscr();

    //initialisation aléatoire
    srand(time(NULL));

    // entrées clavier
    keypad(win, true); //active les touches spéciales (flèches)
    nodelay(win,true);//permet de lire l'entrée du joueur en permanance
    curs_set(0); //masque le curseur

    //initialisation taille
    int taille = 1;
    //initialisation plateau
    char plateau[TAILLEY][TAILLEX];
    initPlateau(plateau); 

    //snake au démarrage
    Tab2 tete = {TAILLEX/2,TAILLEY/2}; //coordonnées tête
    Tab2 dir={0,0}; //direction
    Tab2 corps[(TAILLEX-2)*(TAILLEY-2)]={tete,tete};

    //pomme
    int tlogCellulesVides;
    int cellulesVides[(TAILLEX-2)*(TAILLEY-2)][2];
    creerTableauSansSerpent(plateau,cellulesVides,&tlogCellulesVides);

    placerPomme(plateau,cellulesVides,tlogCellulesVides);
    
    //initialisation
    int surPomme=0,collision=0;

    //gameloop
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
        collision=0;
        tete=deplacementTete(plateau,tete,dir);
        testCollisions(plateau,tete,&surPomme,&collision);

        majPlateau(plateau,corps,tete,taille,dir);
        
        if(surPomme==1){
            creerTableauSansSerpent(plateau,cellulesVides,&tlogCellulesVides);
            placerPomme(plateau,cellulesVides,tlogCellulesVides);
            taille++;
        }

        //affichage
        erase();
        affichPlateau(plateau);
        refresh();//sinon le plateau n'a pas le temps de s'afficher complétement et le usleep() s'active
        if(collision==1){
            usleep(INTERVALLE*200000);
            break;
        }
        if(taille==(TAILLEX-2)*(TAILLEY-2)){//si le serpent à atteint la taille maximale
            usleep(INTERVALLE*3*100000);
            break;
        }
        usleep(INTERVALLE*100000);
        

    }

    endwin();
    printf("votre taille finale: %d\n",taille);
    if(taille==(TAILLEX-2)*(TAILLEY-2)){
        printf("incroyable, vous avez mangé toutes les pommes!\n");
    }
    return 0;
}