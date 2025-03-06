#include "shellsnake.h"


//faire type enum plutot pour vitesse et hauteur et largeur
//mettre durée fixe pour intervalle mort et gagne

int lancerPartie(int largeur, int hauteur,int vitesse){
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
    char **plateau;
    plateau=allouerPlateau(hauteur,largeur);
    // char plateau[hauteur][largeur];
    initPlateau(plateau,largeur,hauteur); 

    //snake au démarrage
    Tab2 tete = {largeur/2,hauteur/2}; //coordonnées tête
    Tab2 dir={0,0}; //direction
    Tab2 corps[(largeur-2)*(hauteur-2)];//={tete,tete};
    corps[0]=tete;
    corps[1]=tete;

    //pomme
    int tlogCellulesVides;
    int cellulesVides[(largeur-2)*(hauteur-2)][2];
    creerTableauSansSerpent(plateau,largeur,hauteur,cellulesVides,&tlogCellulesVides);

    placerPomme(plateau,largeur,hauteur,cellulesVides,tlogCellulesVides);
    
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
        tete=deplacementTete(plateau,largeur,hauteur,tete,dir);
        testCollisions(plateau,largeur,hauteur,tete,&surPomme,&collision);

        majPlateau(plateau,largeur,hauteur,corps,tete,taille,dir);
        
        if(surPomme==1){
            creerTableauSansSerpent(plateau,largeur,hauteur,cellulesVides,&tlogCellulesVides);
            placerPomme(plateau,largeur,hauteur,cellulesVides,tlogCellulesVides);
            taille++;
        }

        //affichage
        erase();
        affichPlateau(plateau,largeur,hauteur);
        refresh();//sinon le plateau n'a pas le temps de s'afficher complétement et le usleep() s'active
        if(collision==1){
            usleep(vitesse*800000);
            break;
        }
        if(taille==(largeur-2)*(hauteur-2)){//si le serpent à atteint la taille maximale
            usleep(vitesse*10*100000);
            break;
        }
        usleep(vitesse*100000);
        

    }

    endwin();
    libererPlateau(plateau,hauteur);
    return taille;
}

int main(void){
    int score,largeur=5,hauteur=5;
    score=lancerPartie(largeur,hauteur,3);
    printf("votre taille finale: %d\n",score);
    if(score==(largeur-2)*(hauteur-2)){
        printf("incroyable, vous avez mangé toutes les pommes!\n");
    }
    
    return 0;
}