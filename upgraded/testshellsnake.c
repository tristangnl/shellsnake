#include "shellsnake.h"


//faire type enum plutot pour vitesse et hauteur et largeur
//file bestscore
//afficher nom du jeu sur menu
//ajouter option personnalisé pour choisir une taille ou vitesse personnalisé saisie controlée en x et y pour la taille
//mettre tout en francais ou tout en anglais
//ajouter nbPomme?
//plus ajouter commandes sur le menu?//sur droite quand on va sur le start par exemple

int lancerPartie(int largeur, int hauteur,int vitesse){
    //initialisation plateau
    char **plateau;
    plateau=allouerPlateau(hauteur,largeur);
    
    //initialisation fenêtre(ncurses)
    WINDOW *win = initscr();
    box(win, 0, 0);  // Dessine un cadre autour de la fenêtre

    //initialisation aléatoire
    srand(time(NULL));

    // entrées clavier
    keypad(win, true); //active les touches spéciales (flèches)
    nodelay(win,true);//permet de lire l'entrée du joueur en permanance
    curs_set(0); //masque le curseur

    //initialisation taille
    int taille = 1;
    
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
        if(fleche=='q'){
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
            usleep(800000);
            break;
        }
        if(taille==(largeur-2)*(hauteur-2)){//si le serpent à atteint la taille maximale
            usleep(1000000);
            break;
        }
        usleep(vitesse*100000);
        

    }

    endwin();
    libererPlateau(plateau,hauteur);
    return taille;
}

void afficheMenu(WINDOW *win,char *color,char size[][10],char speed[][10],int pos,int itsize,int itspeed){
    switch(pos){
        case 1: 
            wprintw(win,"\n color  <%s>\n",color);
            wprintw(win," size   %s   \n",size[itsize]);
            wprintw(win," speed  %s   \n",speed[itspeed]);
            wprintw(win,"\tstart\n");
        break;
        case 2:
            wprintw(win,"\n color   %s \n",color);
            wprintw(win," size  <%s>  \n",size[itsize]);
            wprintw(win," speed  %s   \n",speed[itspeed]);
            wprintw(win,"\tstart\n");
            break;
        case 3:
            wprintw(win,"\n color   %s \n",color);
            wprintw(win," size   %s   \n",size[itsize]);
            wprintw(win," speed <%s>  \n",speed[itspeed]);
            wprintw(win,"\tstart\n");
            break;
        case 4:
            wprintw(win,"\n color   %s \n",color);
            wprintw(win," size   %s   \n",size[itsize]);
            wprintw(win," speed  %s   \n",speed[itspeed]);
            wprintw(win,"      < start >\n");
            break;
    }


    



}
void menu(void){
    initscr();
    noecho();
    curs_set(0); //masque le curseur

    int pos=4,score;
    WINDOW *win= newwin(6,23,0,0);
    keypad(win, true); //active les touches spéciales (flèches)
    char speed[3][10]={"  lent   ","  moyen  ","  rapide "};
    char size[3][10]={"  petit  ","  moyen  ","  grand  "};
    int itspeed=1,itsize=1;
    
    afficheMenu(win," default ",size,speed,pos,itsize,itspeed);
    box(win, 0, 0);
    int fleche = wgetch(win);
    
    while(true){
        if (fleche == KEY_LEFT){
            if(pos==3){
                if(itspeed==0){
                    itspeed=2;
                }
                else itspeed--;
            }
            else if(pos==2){
                if(itsize==0){
                    itsize=2;
                }
                else itsize--;
            }
        }
        if (fleche == KEY_RIGHT){
            if(pos==3){
                if(itspeed==2){
                    itspeed=0;
                }
                else itspeed++;
            }
            else if(pos==2){
                if(itsize==2){
                    itsize=0;
                }
                else itsize++;
            }
        }
        if (fleche == KEY_DOWN){
            if(pos==4) pos=1;
            else pos++;
        }   
        if (fleche == KEY_UP){
            if(pos==1) pos=4;
            else pos--;
            
        }
        if(fleche=='q'){//echap
            break;
        }
        if(fleche=='\n'){
            if(pos==4){
                int vitesse,hauteur,largeur;
                switch(itspeed){
                    case 0:
                        vitesse=3;
                    break;
                    case 1:
                        vitesse=2;
                    break;
                    case 2:
                        vitesse=1;
                    break;
                }
                switch(itsize){
                    case 0:
                        hauteur=13;
                        largeur=21;
                    break;
                    case 1:
                        hauteur=19;
                        largeur=31;
                    break;
                    case 2:
                        hauteur=25;
                        largeur=41;
                    break;
                }
                score=lancerPartie(largeur,hauteur,vitesse);
                clear();
                refresh();
            //ajt affichage score
            } 
            
            else pos++;
        }
        

        werase(win);
        afficheMenu(win," default ",size,speed,pos,itsize,itspeed);
        box(win, 0, 0);
        wrefresh(win);
        fleche = wgetch(win);
    }
    endwin();

}

int main(void){
    // int score,largeur=4,hauteur=5;//minimum 5 dans chaque
    // score=lancerPartie(largeur,hauteur,3);
    // printf("votre taille finale: %d\n",score);
    // if(score==(largeur-2)*(hauteur-2)){
    //     printf("incroyable, vous avez mangé toutes les pommes!\n");
    // }
    menu();
    return 0;
}