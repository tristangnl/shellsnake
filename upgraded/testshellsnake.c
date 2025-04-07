#include "shellsnake.h"

//mettre tout en francais ou tout en anglais
//ajouter dans readme qu'il faut compiler avec -lncurses
//ajouter dans readme daller dans trgenouelr/public/ShellSnake / ou que le script est disponible dans mon home public/ShellSnake à l'iut



int lancerPartie(int largeur, int hauteur,float vitesse,int nbPommes){
    //initialisation plateau
    char **plateau;
    plateau=allouerPlateau(hauteur,largeur);
    
    //initialisation fenêtre(ncurses)
    WINDOW *winsnake = initscr();
    box(winsnake, 0, 0);  // Dessine un cadre autour de la fenêtre

    //initialisation aléatoire
    srand(time(NULL));

    // entrées clavier
    keypad(winsnake, true); //active les touches spéciales (flèches)
    nodelay(winsnake,true);//permet de lire l'entrée du joueur en permanance
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
    for(int itPommes=1;itPommes<=nbPommes;itPommes++){
        creerTableauSansSerpent(plateau,largeur,hauteur,cellulesVides,&tlogCellulesVides);
        if(tlogCellulesVides>0){
            placerPomme(plateau,largeur,hauteur,cellulesVides,tlogCellulesVides);
        }
    }
    //initialisation
    int surPomme,collision;

    //gameloop
    while(true){
        int fleche = wgetch(winsnake);
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
        
        surPomme=FALSE;

        tete=deplacementTete(plateau,largeur,hauteur,tete,dir);
        testCollisions(plateau,largeur,hauteur,tete,&surPomme,&collision);

        // majPlateau(plateau,largeur,hauteur,corps,tete,taille,dir);
        
        // if(surPomme==TRUE){
        //     creerTableauSansSerpent(plateau,largeur,hauteur,cellulesVides,&tlogCellulesVides);
        //     if(tlogCellulesVides!=0){
        //         placerPomme(plateau,largeur,hauteur,cellulesVides,tlogCellulesVides);
        //     }
        //     taille++;
        // }


        
        if(surPomme==TRUE){
            taille++;
            majPlateau(plateau,largeur,hauteur,corps,tete,taille,dir);
            creerTableauSansSerpent(plateau,largeur,hauteur,cellulesVides,&tlogCellulesVides);
            if(tlogCellulesVides!=0){
                placerPomme(plateau,largeur,hauteur,cellulesVides,tlogCellulesVides);
            }
        }
        else majPlateau(plateau,largeur,hauteur,corps,tete,taille,dir);


        //affichage
        erase();
        affichPlateau(plateau,largeur,hauteur);
        wprintw(winsnake,"\tsize: %d",taille);
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

void afficheMenu(WINDOW *win1,WINDOW *win2,char colorArray[][10],char sizeArray[][10],char speedArray[][10],int pos,int itsize,int itspeed,int itcolor,int nbPommes,int score){
    werase(win1);
    werase(win2);
    if(itcolor!=0){
            wattron(win1,COLOR_PAIR(itcolor));
            wattron(win2,COLOR_PAIR(itcolor));

    }
    mvwprintw(win1,2,3, "  /$$$$$$  /$$                 /$$ /$$     /ooooooooo                      /oo                \n");
    mvwprintw(win1,3,3, " /$$__  $$| $$                | $$| $$    /oo_____  oo                    | oo                \n");
    mvwprintw(win1,4,3, "| $$  \\__/| $$$$$$$   /$$$$$$ | $$| $$   | oo     \\__/ /ooooooo   /oooooo | oo   /oo  /oooooo \n");
    mvwprintw(win1,5,3, "|  $$$$$$ | $$__  $$ /$$__  $$| $$| $$   |  oooooo  | | oo__  oo |____  oo| oo  /oo/ /oo__  oo\n");
    mvwprintw(win1,6,3, " \\____  $$| $$  \\ $$| $$$$$$$$| $$| $$  /\\\\____  oo ^ | oo  \\ oo  /ooooooo| oooooo/ | oooooooo\n");
    mvwprintw(win1,7,3, " /$$  \\ $$| $$  | $$| $$_____/| $$| $$ /oo     \\ oo   | oo  | oo /oo__  oo| oo_  oo | oo_____/\n");
    mvwprintw(win1,8,3, "|  $$$$$$/| $$  | $$|  $$$$$$$| $$| $$|  ooooooooo/   | oo  | oo|  ooooooo| oo \\  oo|  oooooooo\n");
    mvwprintw(win1,9,3, " \\______/ |__/  |__/ \\_______/|__/|__/ \\_________/    |__/  |__/ \\_______/|__/  \\__/ \\_______/\n");
    switch(pos){
        case 1: 
            mvwprintw(win1,12,3,"color  <%s>",colorArray[itcolor]);
            mvwprintw(win1,13,3,"size    %s",sizeArray[itsize]);
            mvwprintw(win1,14,3,"speed   %s",speedArray[itspeed]);
            mvwprintw(win1,15,3,"apples      %d",nbPommes);
            mvwprintw(win1,16,3,"\t start");
        break;
        case 2:
            mvwprintw(win1,12,3,"color   %s",colorArray[itcolor]);
            mvwprintw(win1,13,3,"size   <%s>",sizeArray[itsize]);
            mvwprintw(win1,14,3,"speed   %s",speedArray[itspeed]);
            mvwprintw(win1,15,3,"apples      %d",nbPommes);
            mvwprintw(win1,16,3,"\t start");
            break;
        case 3:
            mvwprintw(win1,12,3,"color   %s",colorArray[itcolor]);
            mvwprintw(win1,13,3,"size    %s",sizeArray[itsize]);
            mvwprintw(win1,14,3,"speed  <%s>",speedArray[itspeed]);
            mvwprintw(win1,15,3,"apples      %d",nbPommes);
            mvwprintw(win1,16,3,"\t start");
            break;
        case 4:
            mvwprintw(win1,12,3,"color   %s",colorArray[itcolor]);
            mvwprintw(win1,13,3,"size    %s",sizeArray[itsize]);
            mvwprintw(win1,14,3,"speed   %s",speedArray[itspeed]);
            mvwprintw(win1,15,3,"apples <    %d    >",nbPommes);
            mvwprintw(win1,16,3,"      start");
            break;
        case 5:
            mvwprintw(win1,12,3,"color   %s",colorArray[itcolor]);
            mvwprintw(win1,13,3,"size    %s",sizeArray[itsize]);
            mvwprintw(win1,14,3,"speed   %s",speedArray[itspeed]);
            mvwprintw(win1,15,3,"apples      %d",nbPommes);
            mvwprintw(win1,16,3,"   <  start  >");
            break;
    }
    box(win1, 0, 0);
    wprintw(win2,"\n  controls:\t\t\tbrief:\n");
    wprintw(win2,"\n  arrows: select/move\t\tEat as many apples\n");//Eat as many apples as you can without hitting the walls or yourself
    wprintw(win2,"  enter/space: accept\t\tas you can without\n");
    wprintw(win2,"  q: quit/exit\t\t\tcrashing !\n");
    box(win2, 0, 0);
    if(score!=-1){
            mvwprintw(win1,17,4,"final size: %d",score);
    }
    if(itcolor!=0){
        wattroff(win2,COLOR_PAIR(itcolor));
        wattroff(win1,COLOR_PAIR(itcolor));

    }
    wrefresh(win1);
    wrefresh(win2);
}



int customMenuSize(int isSize,int isSpeed,int *width,int *height,float *speed,int itcolor){
    WINDOW *wincustom= newwin(8,18,11,22);
    keypad(wincustom, true);
    
    wattron(wincustom,COLOR_PAIR(itcolor));
    wattron(wincustom,COLOR_PAIR(itcolor));


    int tmpwidth=(*width),tmpheight=(*height);
    float speedselector=((0.1-(*speed))/0.1)+50;
    int key=-1;
    if(isSize==TRUE){
        while(key!='\n' && key!=' '){
            werase(wincustom);
            if(tmpwidth-2<10){
                mvwprintw(wincustom,1,2,"width   < %d  >",tmpwidth-2);
            }
            else{
                mvwprintw(wincustom,1,2,"width   < %d >",tmpwidth-2);
            }
            box(wincustom,0,0);
            key=wgetch(wincustom);
            if(key==KEY_LEFT && tmpwidth>5){
                tmpwidth=tmpwidth-2;
            }
            else if(key==KEY_RIGHT && tmpwidth<51){
                tmpwidth=tmpwidth+2;
            }
            else if(key=='q'){
                return TRUE;
            }
        }
        key=-1;
        while(key!='\n' && key!=' '){
            werase(wincustom);
            if(tmpwidth-2<10){
                mvwprintw(wincustom,1,2,"width   < %d  >",tmpwidth-2);
            }
            else{
                mvwprintw(wincustom,1,2,"width   < %d >",tmpwidth-2);
            }
            if(tmpheight-2<10){
                mvwprintw(wincustom,2,2,"height  < %d  >",tmpheight-2);
            }
            else{
                mvwprintw(wincustom,2,2,"height  < %d >",tmpheight-2);

            }
            box(wincustom,0,0);
            key=wgetch(wincustom);
            if(key==KEY_LEFT && tmpheight>5){
                tmpheight=tmpheight-2;
            }
            else if(key==KEY_RIGHT && tmpheight<51){
                tmpheight=tmpheight+2;
            }
            else if(key=='q'){
                return TRUE;
            }
        }
    }
    if(isSpeed==TRUE){
        key=-1;
        while(key!='\n' && key!=' '){
            werase(wincustom);
            if(speedselector<10){
                mvwprintw(wincustom,3,2,"speed   < %.0f  >",speedselector);
            }
            else{
                mvwprintw(wincustom,3,2,"speed   < %.0f >",speedselector);
            }
            if(isSize==TRUE){
                if(tmpwidth-2<10){
                    mvwprintw(wincustom,1,2,"width   < %d  >",tmpwidth-2);
                }
                else{
                    mvwprintw(wincustom,1,2,"width   < %d >",tmpwidth-2);
                }
                if(tmpheight-2<10){
                    mvwprintw(wincustom,2,2,"height  < %d  >",tmpheight-2);
                }
                else{
                    mvwprintw(wincustom,2,2,"height  < %d >",tmpheight-2);
                }
            }
            box(wincustom,0,0);
            key=wgetch(wincustom);
            if(key==KEY_LEFT && speedselector>1){
                speedselector=speedselector-1;
            }
            else if(key==KEY_RIGHT && speedselector<49){
                speedselector=speedselector+1;
            }
            else if(key=='q'){
                return TRUE;
            }
        }
    }
    (*width)=tmpwidth;
    (*height)=tmpheight;
    (*speed)= 0.1 + (50 - speedselector) * 0.1;//0.1: vitesse minimale, 50: plus grand int possible pour l'utilisateur, 0.2: pas entre chaque intervalle
        //permet de convertir un int en un intervalle entre deux frame pour determiner la vitesse du serpent
        //en fonction de speedselector compris entre 1 et 50, cela va donner un float interval entre 0.1 et 9.9 avec un pas de 0.2
    
    delwin(wincustom); 
    return FALSE;
}

void menu(void){
    initscr();
    noecho();
    curs_set(0); //masque le curseur

    if (!has_colors()) {  // permet de vérifier si le terminal supporte ncurses en général
        endwin();
        printf("Votre terminal ne supporte pas les couleurs et la gestion des fenêtres.\n");
        exit(1);
    }

    start_color();
    use_default_colors();
    //initialisations des couples de couleurs(police,arrière plan)
    init_pair(1, COLOR_WHITE,-1);
    init_pair(2, COLOR_RED,-1);
    init_pair(3, COLOR_GREEN,-1);
    init_pair(4, COLOR_YELLOW,-1);
    init_pair(5, COLOR_BLUE,-1);
    init_pair(6, COLOR_MAGENTA,-1);
    init_pair(7, COLOR_CYAN,-1);
    init_pair(8, COLOR_BLACK,-1);

    int hauteur=19,largeur=31;
    float speed=1.5;

    int pos=4,score=-1;
    WINDOW *win1= newwin(20,100,0,0);
    WINDOW *win2= newwin(8,58,11,40);


    keypad(win1, true); //active les touches spéciales (flèches)
    char speedArray[4][10]={" slow    "," medium  "," fast    "," custom  "};
    char sizeArray[4][10]={" small   "," medium  "," large   "," custom  "};
    char colorArray[9][10]={" default "," white   "," red     "," green   "," yellow  "," blue    "," magenta "," cyan    "," black   "};
    int itspeed=1,itsize=1,itcolor=0;
    int nbPommes=1;
    afficheMenu(win1,win2,colorArray,sizeArray,speedArray,pos,itsize,itspeed,itcolor,nbPommes,score);
    
    int fleche = wgetch(win1);
    
    while(true){
        if (fleche == KEY_LEFT){
            if(pos==4){
                if(nbPommes==1){
                    nbPommes=9;
                }
                else nbPommes--;
            }
            else if(pos==3){
                if(itspeed==0){
                    itspeed=3;
                }
                else itspeed--;
            }
            else if(pos==2){
                if(itsize==0){
                    itsize=3;
                }
                else itsize--;
            }
            else if(pos==1){
                if(itcolor==0){
                    itcolor=8;
                }
                else itcolor--;
            }
        }
        else if (fleche == KEY_RIGHT){
            if(pos==4){
                if(nbPommes==9){
                    nbPommes=1;
                }
                else nbPommes++;
            }
            else if(pos==3){
                if(itspeed==3){
                    itspeed=0;
                }
                else itspeed++;
            }
            else if(pos==2){
                if(itsize==3){
                    itsize=0;
                }
                else itsize++;
            }
            else if(pos==1){
                if(itcolor==8){
                    itcolor=0;
                }
                else itcolor++;
            }
        }
        else if (fleche == KEY_DOWN){
            if(pos==5) pos=1;
            else pos++;
        }   
        else if (fleche == KEY_UP){
            if(pos==1) pos=5;
            else pos--;
        }
        else if(fleche=='q'){
            break;
        }
        else if(fleche=='\n' || fleche==' '){
            if(pos==5){
                int exit=FALSE;
                int isSpeed=FALSE,isSize=FALSE;
                switch(itspeed){
                    case 0:
                        speed=2.5;
                    break;
                    case 1:
                        speed=1.5;
                    break;
                    case 2:
                        speed=1;
                    break;
                    case 3:
                        isSpeed=TRUE;
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
                    case 3:
                        isSize=TRUE;
                    break;
                }
                if(isSize==TRUE||isSpeed==TRUE){
                    exit=customMenuSize(isSize,isSpeed,&largeur,&hauteur,&speed,itcolor);
                }
                if(exit==FALSE){
                    attron(COLOR_PAIR(itcolor));
                    score=lancerPartie(largeur,hauteur,speed,nbPommes);
                    flushinp();//efface le buffer des touches préssés lors de la partie, pour ne pas influencer l'affichage du menu 
                    attroff(COLOR_PAIR(itcolor));
                    clear();
                    refresh();
                }
            }
            else if(pos!=5){
                pos++;
            }
        }
        
        //affichage

        afficheMenu(win1,win2,colorArray,sizeArray,speedArray,pos,itsize,itspeed,itcolor,nbPommes,score);

        fleche = wgetch(win1);

    }
    endwin();

}

int main(void){
    menu();
    return 0;
}