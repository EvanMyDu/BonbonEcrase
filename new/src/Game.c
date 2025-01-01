#include <stdio.h>
#include <SDL_render.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <windows.h>
#include <time.h>
#include "../header/Game.h"
#include "../header/AfficheFenetre.h"
#include "../header/Button.h"
#include "../header/score.h"

int rang_suppression[100];
static int nombre_consecutif = 0;

int SetGameMode(int a) {
    return a;
}

void creer_grille(SDL_Renderer* renderer, int gamemode) { //Prend en paramètre le renderer et le gamemode
    srand(time(NULL));
    if (gamemode == 1) { //Si le gamemode vaut 1
        for (int i = 0; i < (largeur_grille*hauteur_grille); i++) { //On créer une grille de la taille choisis pour le mode puzzle
            CreerBoutonJeu(renderer, (((GetSystemMetrics(SM_CXSCREEN)/(largeur_grille+1))*(i%largeur_grille)) + (GetSystemMetrics(SM_CXSCREEN)/(largeur_grille+1))), (GetSystemMetrics(SM_CYSCREEN)/hauteur_grille+2)*(i/largeur_grille), 50, 50, i);
            couleur_boutons[i] = choix_couleur();
        }
    }
    if (gamemode == 2) { //Si le gamemode vaut 2
        for (int i = largeur_grille; i < (largeur_grille*hauteur_grille) + largeur_grille; i++) { //Créer tout les bonbons mais ne leur donne pas de couleur
            CreerBoutonJeu(renderer, (((GetSystemMetrics(SM_CXSCREEN)/(largeur_grille+1))*(i%largeur_grille)) + (GetSystemMetrics(SM_CXSCREEN)/(largeur_grille+1))), (GetSystemMetrics(SM_CYSCREEN)/hauteur_grille+2)*((i/largeur_grille)-1), 50, 50, i);
        }
        for (int j = (largeur_grille*hauteur_grille) + largeur_grille - 1; j > ((hauteur_grille-2)*largeur_grille) - 1; j--) {
            //Donne une couleur uniquement aux bonbons des trois dernière colonne (colonne du bas)
            couleur_boutons[j] = choix_couleur();
        }
    }
}

void remonter_couleur() { //Remonte la couleur de tout les bonbons de la grille (utiliser pour le mode rush)
    for (int i = 0; i < ((largeur_grille*hauteur_grille)); i++) {
        couleur_boutons[i] = couleur_boutons[i + largeur_grille];
        couleur_boutons[i+largeur_grille] = 0;
    }
}

void ajouter_ligne() { //Ajoute une ligne de couleur aléatoire à la dernière ligne (mode rush)
    for (int i = ((largeur_grille*hauteur_grille)); i < (largeur_grille*hauteur_grille) + largeur_grille; i++) {
        couleur_boutons[i] = choix_couleur(); //Met une couleur aléatoire pour chaque bonbon de la dernière ligne (qui n'ont pas de couleur car les bonbons ont été remonté au préalables)
    }
}

int deja_enregistrer(int indice_echange) { //Prend en paramètre d'entrée l'indice à échanger
    for (int i = 0; i < 100; i++) {
        if (indice_echange == rang_suppression[i]) { //Si indice_echange est déjà présent dans le tableau d'entier rang_suppression
            return 1; //On renvoie 1 (True)
        }
    }
    return 0; //Si indice_echange n'est pas présent dans le tableau rang_suppression, alors on renvoie 0 (False)
}

void check_bonbon_alentours(int indice_echange) {
    int temp_indice_echange = indice_echange; // On sauvegarde l'indice à échanger

    // Vérification vers la droite
    if ((indice_echange % largeur_grille != largeur_grille - 1) && (couleur_boutons[indice_echange] != 0)) { // Si l'indice n'est pas dans la dernière colonne et que le bonbon a une couleur
        while ((indice_echange % largeur_grille < largeur_grille - 1) && (couleur_boutons[indice_echange] == couleur_boutons[indice_echange + 1])) { // Tant qu'on reste dans la grille et que les couleurs sont identiques
            if (deja_enregistrer(indice_echange) == 0) { // Si l'indice actuel n'est pas encore enregistré
                rang_suppression[nombre_consecutif] = indice_echange; // Enregistre l'indice
                nombre_consecutif++; // Incrémente le nombre de bonbons consécutifs
            }
            if (deja_enregistrer(indice_echange + 1) == 0) { // Si l'indice suivant n'est pas encore enregistré
                rang_suppression[nombre_consecutif] = indice_echange + 1; // Enregistre l'indice suivant
                nombre_consecutif++; // Incrémente le nombre de bonbons consécutifs
            }
            indice_echange++; // Passe à l'indice suivant
        }
        indice_echange = temp_indice_echange; // Réinitialise l'indice
    }

    // Vérification vers la gauche
    if ((indice_echange % largeur_grille != 0) && (couleur_boutons[indice_echange] != 0)) { // Si l'indice n'est pas dans la première colonne et que le bonbon a une couleur
        while ((indice_echange % largeur_grille > 0) && (couleur_boutons[indice_echange] == couleur_boutons[indice_echange - 1])) { // Tant qu'on reste dans la grille et que les couleurs sont identiques
            if (deja_enregistrer(indice_echange) == 0) { // Si l'indice actuel n'est pas encore enregistré
                rang_suppression[nombre_consecutif] = indice_echange; // Enregistre l'indice
                nombre_consecutif++; // Incrémente le nombre de bonbons consécutifs
            }
            if (deja_enregistrer(indice_echange - 1) == 0) { // Si l'indice précédent n'est pas encore enregistré
                rang_suppression[nombre_consecutif] = indice_echange - 1; // Enregistre l'indice précédent
                nombre_consecutif++; // Incrémente le nombre de bonbons consécutifs
            }
            indice_echange--; // Passe à l'indice précédent
        }
        indice_echange = temp_indice_echange; // Réinitialise l'indice
    }

    // Vérification vers le haut
    if ((indice_echange >= largeur_grille) && (couleur_boutons[indice_echange] != 0)) { // Si l'indice n'est pas dans la première ligne et que le bonbon a une couleur
        while ((indice_echange >= largeur_grille) && (couleur_boutons[indice_echange] == couleur_boutons[indice_echange - largeur_grille])) { // Tant qu'on reste dans la grille et que les couleurs sont identiques
            if (deja_enregistrer(indice_echange) == 0) { // Si l'indice actuel n'est pas encore enregistré
                rang_suppression[nombre_consecutif] = indice_echange; // Enregistre l'indice
                nombre_consecutif++; // Incrémente le nombre de bonbons consécutifs
            }
            if (deja_enregistrer(indice_echange - largeur_grille) == 0) { // Si l'indice au-dessus n'est pas encore enregistré
                rang_suppression[nombre_consecutif] = indice_echange - largeur_grille; // Enregistre l'indice au-dessus
                nombre_consecutif++; // Incrémente le nombre de bonbons consécutifs
            }
            indice_echange = indice_echange - largeur_grille; // Passe à l'indice au-dessus
        }
        indice_echange = temp_indice_echange; // Réinitialise l'indice
    }

    // Vérification vers le bas
    if ((indice_echange <= hauteur_grille * largeur_grille - largeur_grille - 1) && (couleur_boutons[indice_echange] != 0)) { // Si l'indice n'est pas dans la dernière ligne et que le bonbon a une couleur
        while ((indice_echange <= hauteur_grille * largeur_grille - largeur_grille - 1) && (couleur_boutons[indice_echange] == couleur_boutons[indice_echange + largeur_grille])) { // Tant qu'on reste dans la grille et que les couleurs sont identiques
            if (deja_enregistrer(indice_echange) == 0) { // Si l'indice actuel n'est pas encore enregistré
                rang_suppression[nombre_consecutif] = indice_echange; // Enregistre l'indice
                nombre_consecutif++; // Incrémente le nombre de bonbons consécutifs
            }
            if (deja_enregistrer(indice_echange + largeur_grille) == 0) { // Si l'indice en dessous n'est pas encore enregistré
                rang_suppression[nombre_consecutif] = indice_echange + largeur_grille; // Enregistre l'indice en dessous
                nombre_consecutif++; // Incrémente le nombre de bonbons consécutifs
            }
            indice_echange = indice_echange + largeur_grille; // Passe à l'indice en dessous
        }
        indice_echange = temp_indice_echange; // Réinitialise l'indice
    }
}

void check_bonbon_identiques(int indice_echange) { //Fonction répétitive mais nous avons préférer la laisser pour ne pas créer de bug
    check_bonbon_alentours(indice_echange);
}

int supprimer_bonbon(int indice, int consecutif) { //La fonction prend en paramètre un indice et le nombre de chaine consecutive
    if (nombre_consecutif >= 4) { //Si la variable static nombre_consecutif est >= à 4, alors on supprime la chaine de bonbon consecutif
        for (int i = 0; i < nombre_consecutif; i++) {
            couleur_boutons[rang_suppression[i]] = 0;
        }
        donner_points(nombre_consecutif, consecutif); //On donne des points pour cette chaine supprimer
        nombre_consecutif = 0; //On remet le nombre de bonbon consecutif à 0
        return consecutif + 1; //On ajoute 1 au nombre de chaine consecutive
    }
    else { //Si la variable static nombre_consecutif est < 4, alors
        nombre_consecutif = 0; //On remet le nombre de bonbon consecutif à 0
        return consecutif; //Et on ajoute pas au nombre de chaine consecutive
    }
}

void reinitialiser_tableau(int tab[]) { //Prends en paramètre un tableau d'entiers
    for (int i = 0; i < 12; i++) { //Pour i allant de 0 à 11
        tab[i] = 0; //On met l'int d'indice i à 0
    }
}

void echange_bonbon(int indice_echange) { //Prends en paramètre l'indice du bonbon à échanger
    int temp_couleur = couleur_boutons[indice_clicked]; //On enregistre la couleur du bonbon qui a été cliqué en premier
    //Si le bonbon à indice_echange et le bonbon à indice_clicked sont à une case d'écart à l'horizontale ou à la verticale
    if (((((indice_echange == indice_clicked + 1) || (indice_echange == indice_clicked - 1)) || ((indice_echange == (indice_clicked - largeur_grille))) || (indice_echange == (indice_clicked + largeur_grille)))) && ((couleur_boutons[indice_echange] != (couleur_boutons[indice_clicked])) && (couleur_boutons[indice_echange] != 0))) {
        couleur_boutons[indice_clicked] = couleur_boutons[indice_echange]; //On echange la couleur des deux bonbons
        couleur_boutons[indice_echange] = temp_couleur;
    }
    else {
        clicked = 0; //Met la variable externe clicked à 0 (False)
    }
}

void tomber_bonbon() {
    for (int i = 0; i < largeur_grille; i++) { //Pour chaque colonne
        for (int j = hauteur_grille - 1; j >= 1; j--) {
            if (couleur_boutons[i + j*largeur_grille] == 0) { //Si la couleur du bonbon est NULL
                int temp_couleur = couleur_boutons[i + (j-1)*largeur_grille]; //On enregistre la couleur à faire tomber
                couleur_boutons[i + (j-1)*largeur_grille] = 0; //On remplace la couleur par 0
                couleur_boutons[i + j*largeur_grille] = temp_couleur; //On descend la couleur d'une ligne
            }
        }
    }
}

int check_color_change() {
    for (int i = 0; i < largeur_grille; i++) { //Regarde la dernière colonne du tableau
        if (couleur_boutons[i] != 0) { //Si la couleur des bonbons n'est plus NULL
            return 1; //Arrête le jeu
        }
    }
    return 0; //Continue le jeu
}

int count_color(int couleur, int last_row_index_start, int last_row_index_end) { //Prends comme paramètre une couleur, qui sera la couleur à compter, un indice de départ et un indice de fin
    int count = 0; //On initialise le nombre de bonbon de la couleur choisie à zéro
    for (int i = 0; i < (hauteur_grille*largeur_grille); i++) {
        //On compte le nombre de bonbon de la même couleur entre les colonnes d'indice ...start et ...end
        if ((i%largeur_grille >= last_row_index_start%largeur_grille) && (i%largeur_grille <= last_row_index_end%largeur_grille)) {
            if (couleur_boutons[i] == couleur) { //Si la couleur choisie est égale à la couleur de l'indice i
                count++; //On ajoute 1 au nombre de bonbon de la couleur des paramètres
            }
        }
    }
    return count; //On renvoie le nombre de bonbon de la même couleur
}

int count_candy_in_col(int last_row_index) { //Prends comme paramètre l'indice de la dernière ligne
    int candy_in_col = 0; //On initialise le nombre de bonbon dans la colonne à zéro
    while (couleur_boutons[last_row_index] != 0) { //Tant qu'il y a un bonbon à l'indice...
        candy_in_col++; //...On ajoute un bonbon au nombre de bonbons compter...
        last_row_index = last_row_index - largeur_grille; //...Et on remonte d'une ligne (on part du bas pour finir en haut)
    }
    return candy_in_col; //Renvoie le nombre de bonbons dans la colonne
}

int check_grid() {
    //On initialise le nombre de carré de chaque couleur dans la grille en entier
    int tot_rouge = count_color(1, 0, largeur_grille - 1), tot_bleu = count_color(2,  0, largeur_grille - 1), tot_jaune = count_color(4,  0, largeur_grille - 1), tot_vert = count_color(3,  0, largeur_grille - 1);
    //Si il n'y a pas plus de 3 bonbons de chaque couleur, comme on ne peux faire aucune combinaison...
    if ((tot_rouge < 4) && (tot_jaune < 4) && (tot_vert < 4) && (tot_bleu < 4)) {
        return 1; //...On arrête le jeu
    }
    //Si le nombre de bonbon d'une seule couleur ou plus est supérieur ou égal à 4
    if(((tot_rouge >= 4) || (tot_jaune >= 4) || (tot_vert >= 4) || (tot_bleu >= 4))) {
        //On regarde si la dernière ligne du tableau est remplie
        for (int i = (largeur_grille*(hauteur_grille-1)); i < (largeur_grille*hauteur_grille)-1; i++) {
            //Si l'une des colonnes de la grille est vide
            if (couleur_boutons[i] == 0) {
                int stop = 0; //On initialise un int qui servira de donneur d'information
                int tot_gauche = 0; //On initialise un int qui sera le totale de bonbon à gauche de la colonne vide
                int tot_droit = 0; //On initialise un int qui sera le totale de bonbon à droite de la colonne vide
                int j = i; //On sauvegarde l'indice de la colonne vide
                while (j != largeur_grille*(hauteur_grille-1)-1) { //Tant que on a pas atteint la case tout en bas à gauche
                    tot_gauche = tot_gauche + count_candy_in_col(j); //On compte le total de bonbon à gauche de la colonne vide
                    j = j - 1; //On décale l'indice de 1 vers la gauche
                }
                if (tot_gauche >= 4) { //Si il y a plus de 3 bonbons à gauche de la colonne vide
                    int tot_rouge_gauche = count_color(1, 0, i), tot_bleu_gauche = count_color(2, 0, i), tot_jaune_gauche = count_color(4, 0, i), tot_vert_gauche = count_color(3, 0, i);
                    //Si il n'y a pas plus de 3 bonbons de la même couleur à gauche
                    if ((tot_rouge_gauche < 4) && (tot_jaune_gauche < 4) && (tot_vert_gauche < 4) && (tot_bleu_gauche < 4)) {
                        stop = 1; //On met stop à 1
                    }
                    //Si il y a au moins 4 bonbons d'une même couleur à gauche, on continue la partie
                    if ((tot_rouge_gauche >= 4) || (tot_jaune_gauche >= 4) || (tot_vert_gauche >= 4) || (tot_bleu_gauche >= 4)) {
                        return 0;
                    }
                }
                //Si il n'y a pas au moins 4 bonbons à gauche, on met stop à 1
                else {
                    stop = 1;
                }
                j = i; //On reinitialise l'indice de j à l'indice de la colonne vide
                while (j != largeur_grille*hauteur_grille) { //Tant que on a pas atteint la colonne tout en bas à droite
                    tot_droit = tot_droit + count_candy_in_col(j); //On compte le nombre total de bonbons à droite de la colonne vide
                    j = j + 1; //On décale l'indice de 1 vers la droite
                }
                if (tot_droit >= 4) { //Si il ya plus de quatre bonbons à droite de la colonne vide
                    int tot_rouge_droit = count_color(1, i, largeur_grille - 1), tot_bleu_droit = count_color(2, i, largeur_grille - 1), tot_jaune_droit = count_color(4, i, largeur_grille - 1), tot_vert_droit = count_color(3, i, largeur_grille - 1);
                    //Si il y a moins de 4 bonbons de couleur identique à droite de la colonne vide
                    if ((tot_rouge_droit < 4) && (tot_jaune_droit < 4) && (tot_vert_droit < 4) && (tot_bleu_droit < 4)) {
                        if (stop == 1) { //Et que il y a moins de 4 bonbons à gauche de la colonne vide ou que il n'y pas plus de 3 bonbons de même couleur à gauche de la colonne vide
                            return 1; //On arrête le jeu
                        }
                    }
                    //Si il y a au moins 4 bonbons de la même couleur à droite
                    if ((tot_rouge_droit >= 4) || (tot_jaune_droit >= 4) || (tot_vert_droit >= 4) || (tot_bleu_droit >= 4)) {
                        return 0; //On continue la partie
                    }
                }
                else { //Si il y a moins de 4 bonbons à droite de la colonne vide
                    if (stop == 1) { //Et que il y a moins de 4 bonbons à gauche de la colonne vide ou que il n'y pas plus de 3 bonbons de même couleur à gauche de la colonne vide
                        return 1; //On arrête la partie
                    }
                }
            }
        }
        return 0; //Si il n'y a aucune colonne vide on continue la partie
    }
    return 0; //Au cas ou la fonction marche mal on continue la partie
}

int end_game(int gamemode) { //Prends en paramètre le mode de jeu actuel
    if (gamemode == 1) { //Si on est en mode puzzle
        return check_grid(); //On renvoie ce que renvoie check_grid, soit 1 soit 0
    }
    if (gamemode == 2) { //Si on est en mode rush
        return check_color_change(); //On regarde si la couleur de la ligne numéro (hauteur grille + 1) est colorié, si oui alors on renvoie 1
    }
    return 0; //Si on est pas en jeu, on renvoie 0
}

void game_loop() {
    char nom[50]; //Initialise le nom
    printf("Entrer votre nom \n");
    scanf("%s", &nom); //Récupère le nom du joueur dans la console
    time_t start = time(NULL); //Initialise start au temps à l'instant t
    time_t current;
    SDL_Init(SDL_INIT_EVERYTHING); //Initialise la bibliotheque SDL
    TTF_Init(); //Initialise la bibliotheque TTF
    SDL_Renderer *renderer = AfficheFenetre(); //Associe à un pointeur l'instance du renderer créer par la fonction AfficheFenetre
    int menu = 1; //Le menu vaut 1 donc TRUE, au lancement du programme nous somme dans le menu
    int jeu = 0; //Le jeu vaut 0 donc FALSE, nous ne somme donc pas en jeu
    int gamemode = 0; //Le gamemode vaut 0 donc nous sommes pas en gamemode
    SDL_bool run = SDL_TRUE; //Tant que ce booléen est TRUE, la boucle de jeu ne s'arrête pas
    while(run) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) //Si on quitte SDL, on arrête la boucle de jeu
            {
                run = SDL_FALSE;
            }
            if (menu == 3) { //Si on est dans le menu de choix du mode de jeu
                if ((event.type == SDL_MOUSEBUTTONDOWN) && (CheckAllRectMenu() == 1)) { //Regarde si le clic-gauche de la souris est pressé et que la souris se trouve dans un rectangle du menu
                    gamemode = GetButtonPurposeMenu(renderer, 3, 4, menu); //Détermine quel bouton a été cliqué et modifie la valeur de menu en fonction de la fonction du bouton
                    if (gamemode == 1 || gamemode == 2) {
                        jeu = 1;
                        menu = 0;
                    }
                    if (gamemode == 1) {
                        creer_grille(renderer, 1); //Si le gamemode vaut 1 on creer une grille de jeu de puzzle
                    }
                    if (gamemode == 2) {
                        creer_grille(renderer, 2); //Si le gamemode vaut 2, on creer une grille de jeu de rush
                    }
                }
            }
            if (menu == 4) { //Si on est dans l'affichage du score
                if ((event.type == SDL_MOUSEBUTTONDOWN) && (CheckAllRectMenu() == 1)) { //Et que on effectue un clique gauche et que notre curseur est dans un rectangle du menu
                    menu = GetButtonPurposeMenu(renderer, 20, 20, menu); //Menu vaut donc ce que renvoie la fonction GetButtonPurposeMenu pour le bouton d'indice 20
                }
            }
            if (menu == 2) { //Si on est dans l'affichage du choix de la taille de la grille
                if ((event.type == SDL_MOUSEBUTTONDOWN) && (CheckAllRectMenu() == 1)) { //Regarde si le clic-gauche de la souris est pressé et que la souris se trouve dans un rectangle du menu
                    //Détermine quel bouton a été cliqué et modifie la valeur de menu en fonction de la fonction du bouton
                    menu = GetButtonPurposeMenu(renderer, 5, 20, menu); //Menu vaut donc ce que renvoie la fonction GetButtonPurposeMenu pour les bouton d'indice 5 à 19
                }
            }
            if (menu == 1) { //Si on est dans le menu principale
                if ((event.type == SDL_MOUSEBUTTONDOWN) && (CheckAllRectMenu() == 1)) { //Regarde si le clic-gauche de la souris est pressé et que la souris se trouve dans un rectangle du menu
                    menu = GetButtonPurposeMenu(renderer, 0, 2, menu); //Détermine quel bouton a été cliqué et modifie la valeur de menu en fonction de la fonction du bouton
                }
            }
            if (jeu == 1) { //Si on est en jeu
                if ((event.type == SDL_MOUSEBUTTONDOWN) && (CheckAllRectGame() == 1)) { //Regarde si le clic-gauche de la souris est pressé et que la souris se trouve dans un rectangle du jeu
                    GetButtonPurposeGame(renderer);
                }
            }

        }
        if (menu == 4) { //Si on est dans l'affichage des scores
            ActualiserFenetreScore(renderer);
        }

        if (menu == 1) { //Si on est dans le menu principale
            ActualiserFenetreMenu(renderer); //Affiche le menu
        }
        if (menu == 3) { //Si on est dans le menu de choix de mode
            ActualiserFenetreChoixMode(renderer);
        }
        if (menu == 2) { //Si on est dans le menu de choix de taille de grille
            ActualiserFenetreChoixGrille(renderer);
        }
        if (jeu == 1) { //Si on est dans le jeu
            ActualiserFenetreJeu(renderer, gamemode); //Affiche le jeu*
            current = time(NULL); //Lance le timer pour le mode rush
            if (gamemode == 1) { //Si on est en mode puzzle
                int a = 0; //Initialise un int pour le nombre de chaine consécutive
                for (int i = 0; i < largeur_grille*hauteur_grille; i++) { //Pour chaque case de la grille on fait
                    reinitialiser_tableau(rang_suppression); //reinitialiser le tableau qui contient les indices des bonbons à supprimer
                    check_bonbon_identiques(i); //on regarde si il y a une chaine de bonbon
                    a = supprimer_bonbon(i, a); //On supprime les bonbons qui constituent une chaine et on ajoute 1 au nombre de chaine consecutive
                    reinitialiser_tableau(rang_suppression); //On reinitialise le tableau qui contient les indices des bonbons à supprimer (mesure de sécurité au cas)
                    tomber_bonbon(); //On fait tomber les bonbons vers le bas
                }
                if (end_game(gamemode) == 1) { //Si la fonction end_game renvoie 1, on arrête le jeu
                    menu = 1; //On passe l'état du menu à True (1)
                    jeu = 0; //On passe l'état du jeu à False (0)
                    sauvegarder_score(nom); //On sauvegarde le score de la partie
                }
            }
            if (gamemode == 2) { //Si on est en mode rush
                if (current - start >= 15) { //Si la différence de temps entre le moment actuelle et le moment ou a été initialisé le timer est supérieure ou égale à 15 secondes
                    remonter_couleur(); //On remonte tout les bonbons d'une ligne
                    ajouter_ligne(); //On ajoute une ligne de bonbon en bas de la grille
                    if (end_game(gamemode) == 1) { //Si la fonction end_game renvoie 1, on arrête le jeu
                        menu = 1; //On passe l'état du menu à True (1)
                        jeu = 0; //On passe l'état du jeu à False (0)
                        sauvegarder_score(nom); //On sauvegarde le score de la partie
                    }
                    start = current; //On réinitialise le timer
                }
                int a = 0; //Initialise un int pour le nombre de chaine consécutive
                for (int i = 0; i < largeur_grille*hauteur_grille; i++) { //Pour chaque case de la grille on fait
                    reinitialiser_tableau(rang_suppression); //reinitialiser le tableau qui contient les indices des bonbons à supprimer
                    check_bonbon_identiques(i); //on regarde si il y a une chaine de bonbon
                    a = supprimer_bonbon(i, a); //On supprime les bonbons qui constituent une chaine et on ajoute 1 au nombre de chaine consecutive
                    reinitialiser_tableau(rang_suppression); //On reinitialise le tableau qui contient les indices des bonbons à supprimer (mesure de sécurité au cas)
                    tomber_bonbon(); //On fait tomber les bonbons vers le bas
                }
            }
        }
    }
    SDL_Quit(); //Si la boucle de jeu s'arrête on quitte SDL
    exit(EXIT_SUCCESS); //On arrête l'execution de l'executable
}
