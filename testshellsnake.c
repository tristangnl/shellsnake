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
    Tab2 corps[TAILLE*TAILLE]={tete,tete};//pour qu'il soit positionné au milieu
    char caractete='^';//caractère de la tête au démarrage du jeu

    //pomme
    int tlogCellulesVides;//initialisation
    int cellulesVides[TAILLE*TAILLE][2];
    creerTableauSansSerpent(plateau,cellulesVides,&tlogCellulesVides);//creer tableau de tt les positions disponibles pour placer une pomme

    placerPomme(plateau,cellulesVides,tlogCellulesVides);//selectionne aléatoirement une case du tableau de positions disponibles pour placer une pomme
    
    //initialisation
    int surPomme=0,collision=0;

    // affichPlateau(TAILLE,plateau);
    //gameloop
    while(true){
        int fleche = wgetch(win);
        if (fleche == KEY_LEFT){//gauche
            if(dir.x == 1) continue;
            dir.x =-1;
            dir.y=0;
        }
        if (fleche == KEY_RIGHT){//droite
            if(dir.x == -1) continue;
            dir.x =1;
            dir.y=0;
        }
        if (fleche == KEY_DOWN){//bas
            if(dir.y == -1) continue;
            dir.x =0;
            dir.y=1;
        }
        if (fleche == KEY_UP){//haut
            if(dir.y == 1) continue;
            dir.x =0;
            dir.y=-1;
        }
        if(fleche=='\e'){//echap
            break;
        }
        
        surPomme=0;
        collision=0;
        tete=deplacementTete(plateau,tete,dir);//determine les nouveaux coordonnées de la tête
        testCollisions(plateau,tete,&surPomme,&collision);//vérifie si la tête est en collision avec un mur, sa queue ou une pomme

        //corps        
        for (int it = taille; it>0; it--){
            corps[it] =corps[it-1];// dernière partie du serpent = avant derniere partie du serpent donc décalage du tableau
        }
        corps[0] = tete;//on ajoute la tête en première position qui à été libéré par le décalage
        
        plateau[corps[1].y][corps[1].x]='o';//la deuxième partie du serpent est son corp(pas besoin de tout réecrire, car le reste du corp va suivre jusqu'à être remplacé par " " vu qu'il est déjà écrit dans le tableau)

        plateau[corps[taille].y][corps[taille].x]=' ';//on efface la dernière partie du corps du serpent sur le plateau
        
        //tete
        if(dir.x==1 && dir.y==0){//droite
            caractete='>';
        }
        else if(dir.x==-1 && dir.y==0){//gauche
            caractete='<';

        }
        else if(dir.x==0 && dir.y==-1){//haut
            caractete='^';
        }
        else if(dir.x==0 && dir.y==1){//bas
            caractete='v';
        }
        plateau[corps[0].y][corps[0].x]=caractete; //on finit par écrire la tête sur la nouvelle position du tableau

        
        if(surPomme==1){
            creerTableauSansSerpent(plateau,cellulesVides,&tlogCellulesVides);
            placerPomme(plateau,cellulesVides,tlogCellulesVides);
            taille++;
        }

        

        //draw
        erase();
        
        affichPlateau(TAILLE,plateau);
        refresh();//sinon le plateau n'a pas le temps de s'afficher complétement et le usleep s'active
        if(collision==1){
            usleep(INTERVALLE*500000);
            break;
        }
        usleep(INTERVALLE*100000);
        

    }

    endwin();
    printf("votre taille finale: %d\n",taille);
    return 0;
}