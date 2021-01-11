#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "othello4x4.h"
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))


// Permet de jouer un coup (placer un pion sur la grille et retourner les pions adverses encadrés)

void jouer(int grille[N][N],int ligne,int colonne,int joueur){
    int i, j;
    int joueur_adverse;
    if (joueur == noir){
        joueur_adverse = blanc;
    }
    else {
        joueur_adverse = noir;
    }
    grille[ligne][colonne] = joueur;

    // Vertical vers le haut
    i = ligne - 1;
    while (case_valide(i, colonne) && grille[i][colonne] == joueur_adverse){
        i--;
    }
    if (case_valide(i, colonne) && grille[i][colonne] == joueur){
        for (int k = i+1; k < ligne; k++){
            grille[k][colonne] = joueur;
        }
    }

    // Vertical vers le bas
    i = ligne + 1;
    while (case_valide(i, colonne) && grille[i][colonne] == joueur_adverse){
        i++;
    }
    if (case_valide(i, colonne) && grille[i][colonne] == joueur){
        for (int k = i-1; k > ligne; k--){
            grille[k][colonne] = joueur;
        }
    }

    // Horizontal vers la droite
    j = colonne + 1;
    while (case_valide(ligne, j) && grille[ligne][j] == joueur_adverse){
        j++;
    }
    if (case_valide(ligne, j) && grille[ligne][j] == joueur){
        for (int k = j-1; k > colonne; k--){
            grille[ligne][k]=joueur;
        }
    }

    // Horizontal vers la gauche
    j = colonne - 1;
    while (case_valide(ligne, j) && grille[ligne][j] == joueur_adverse){
        j--;
    }
    if (case_valide(ligne, j) && grille[ligne][j] == joueur){
        for (int k = j+1; k < colonne; k++){
            grille[ligne][k] = joueur;
        }
    }

    // Diagonale haut gauche
    i = ligne - 1;
    j = colonne - 1;
    while(case_valide(i, j) && grille[i][j] == joueur_adverse){
        i--;
        j--;
    }
    if (case_valide(i, j) && grille[i][j] == joueur){
        i++;
        j++;
        while(grille[i][j] == joueur_adverse){
            grille[i][j] = joueur;
            i++;
            j++;
        }
    }

    // Diagonale haut droite
    i = ligne - 1;
    j = colonne + 1;
    while(case_valide(i, j) && grille[i][j] == joueur_adverse){
        i--;
        j++;
    }
    if (case_valide(i, j) && grille[i][j] == joueur){
        i++;
        j--;
        while(grille[i][j] == joueur_adverse){
            grille[i][j] = joueur;
            i++;
            j--;
        }
    }

    // Diagonale bas gauche
    i = ligne + 1;
    j = colonne - 1;
    while(case_valide(i, j) && grille[i][j] == joueur_adverse){
        i++;
        j--;
    }
    if (case_valide(i, j) && grille[i][j] == joueur){
        i--;
        j++;
        while(grille[i][j] == joueur_adverse){
            grille[i][j] = joueur;
            i--;
            j++;
        }
    }

    // Diagonale bas droite
    i = ligne + 1;
    j = colonne + 1;
    while(case_valide(i, j) && grille[i][j] == joueur_adverse){
        i++;
        j++;
    }
    if (case_valide(i, j) && grille[i][j] == joueur){
        i--;
        j--;
        while(grille[i][j] == joueur_adverse){
            grille[i][j] = joueur;
            i--;
            j--;
        }
    }
}


// Utile dans les parties avec un joeur non machine (permet de rentrer un coup valide)

void entrer_coup(int grille[N][N], int *ligne, int *colonne, int joueur){
    printf ("\nC'est au tour du joueur %d de jouer\n", joueur);
    printf("\nEntrez la ligne correspondant au coup que vous souhaitez jouer :\n");
    scanf("\n%d", ligne);
    printf("\nEntrez la colonne correspondant au coup que vous souhaitez jouer :\n");
    scanf("\n%d", colonne);
    while (!coup_valide(grille, *ligne, *colonne, joueur)){
        printf ("\nCe coup n'est pas valide\nChoisissez une autre case\n");
        printf("\nEntrez la ligne correspondant au coup que vous souhaitez jouer :\n");
        scanf("\n%d", ligne);
        printf("\nEntrez la colonne correspondant au coup que vous souhaitez jouer :\n");
        scanf("\n%d", colonne);
    }
}


// Simule une partie entre deux joueurs (non machine)

void partie_2_joueurs(){
    int joueur = 1;
    int ligne, colonne;

    // Initialisation de la grille
    int grille[N][N];
    initialisation_grille(grille);
    printf("\nDebut de la partie\n");
    affiche_grille(grille);
    printf("\nJoueur 1 : 0 point\nJoueur 2 : 0 point\n");

    // Partie joueur vs joueur
    while(!partie_finie(grille)){
        entrer_coup(grille, &ligne, &colonne, joueur);
        jouer(grille, ligne, colonne, joueur);
        affiche_grille(grille);
        score(grille);
        if (peut_jouer(grille, joueur_suivant(joueur))){
            joueur = joueur_suivant(joueur);
        }
        else {
            printf("\nLe joueur %d passe son tour\n", joueur_suivant(joueur));
        }
    }
    gagnant(grille);

}


//Strategie naive de notre joueur "computer"

void strategie_naive(int grille[N][N], int *ligne, int *colonne, int joueur){
    *ligne = my_rand(N);
    *colonne = my_rand(N);
    while(!coup_valide(grille, *ligne, *colonne, joueur)){
        *ligne = my_rand(N);
        *colonne = my_rand(N);
    }
}


//Strategie "min-max" de profondeur 1 pour notre joueur "computer"

void strategie_minimax1(int grille[N][N], int *ligne, int *colonne, int joueur){
    int l[] = {500, -150, 30, 10, 10, 30, -150, 500,-150, -250, 0, 0, 0, 0, -250, -150,30, 0, 1, 2, 2, 1, 0, 30,10, 0, 2, 16, 16, 2, 0, 10,10, 0, 2, 16, 16, 2, 0, 10,30, 0, 1, 2, 2, 1, 0, 30,-150, -250, 0, 0, 0, 0, -250, -150,500, -150, 30, 10, 10, 30, -150, 500};

    int matrice_heuristique[N][N] ;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
        matrice_heuristique[i][j] = l[i+N*j];
    }
    }
    int score_meilleur_coup = -500;
    for(int i = 0; i < N; i++){
        for(int j=0;j<N;j++){
            if ((coup_valide(grille, i, j, joueur)) && (matrice_heuristique[i][j] > score_meilleur_coup)){
                score_meilleur_coup = matrice_heuristique[i][j];
                *ligne = i;
                *colonne = j;
            }
        }
    }
}


// utile pour effectuer des stats sur le nombre de victoires

int CheckWinner(int grille[N][N], int joueur, int maximizing_player){
    int resultat = gagnant_stat(grille);
    if (maximizing_player){
        if (joueur == resultat){
            return 1;
        }
        else if (resultat == 0){
            return 0;
        }
        else {
            return -1;
        }
    }
    else {
        if (joueur == resultat){
            return -1;
        }
        else if (resultat == 0){
            return 0;
        }
        else {
            return 1;
        }
    }
}



// Algorithme Min-Max

int strategie_minimax(int grille[N][N], int *ligne, int *colonne, int joueur, int maximizing_player, int depth){
    if (partie_finie(grille)){
        return CheckWinner(grille, joueur, maximizing_player);
    }
    if (maximizing_player){
        int value = -100000000;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if (coup_valide(grille, i, j, joueur)){

                    // on copie notre grille
                    int copie_grille[N][N];
                    for(int i = 0; i < N; i++){
                        for(int j = 0; j < N; j++){
                            copie_grille[i][j] = grille[i][j];
                        }
                    }

                    jouer(copie_grille, i, j, joueur);
                    int next_player = joueur_suivant(joueur);
                    int value_bis = value;
                    value = MAX(value, strategie_minimax(copie_grille, ligne, colonne, next_player, 0, depth + 1));
                    if ((value > value_bis) && depth == 0){
                        *ligne = i;
                        *colonne = j;
                    }
                    value_bis = value;
                }
            }
        }
        return value;
    }
    else{
        int value = 100000000;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if (coup_valide(grille, i, j, joueur)){

                    // on copie notre grille
                    int copie_grille[N][N];
                    for(int i = 0; i < N; i++){
                        for(int j = 0; j < N; j++){
                            copie_grille[i][j] = grille[i][j];
                        }
                    }

                    jouer(copie_grille, i, j, joueur);
                    int next_player = joueur_suivant(joueur);
                    int value_bis = value;
                    value = MIN(value, strategie_minimax(copie_grille, ligne, colonne, next_player, 1, depth + 1));
                    if ((value < value_bis) && depth == 0){
                        *ligne = i;
                        *colonne = j;
                    }
                    value_bis = value;
                }
            }
        }
        return value;
    }
}


//Simule une partie entre un joueur et l'ordinateur

void partie_vs_computer(){
    int joueur = 1;
    int ligne, colonne;

    printf("\nVous êtes le joueur 1 !");

    // Choix de la strategie du joueur "computer"
    int strategie;
    printf("\nQuelle strategie souhaitez-vous utiliser pour le joueur ordinateur ?\n1 = naif\n2 = minimax\n");
    scanf("\n%d", &strategie);

    // Initialisation de la grille
    int grille[N][N];
    initialisation_grille(grille);
    printf("\nDebut de la partie\n");
    affiche_grille(grille);
    printf("\nJoueur 1 : 0 point\nJoueur 2 : 0 point\n");

    // Partie joueur vs machine
    while(!partie_finie(grille)){
        if (joueur == 1){
            entrer_coup(grille, &ligne, &colonne, joueur);
            jouer(grille, ligne, colonne, joueur);
            affiche_grille(grille);
            score(grille);
            if (peut_jouer(grille, joueur_suivant(joueur))){
                joueur = joueur_suivant(joueur);
            }
            else{
                printf("\nLe joueur %d passe son tour\n", joueur_suivant(joueur));
            }
        }
        else{
            if (strategie == 1){
                strategie_naive(grille, &ligne, &colonne, joueur);
            }
            else{
                strategie_minimax(grille, &ligne, &colonne, joueur, 1, 0);
            }
            jouer(grille, ligne, colonne, joueur);
            affiche_grille(grille);
            score(grille);
            if (peut_jouer(grille, joueur_suivant(joueur))){
                joueur = joueur_suivant(joueur);
            }
            else{
                printf("\nLe joueur %d passe son tour\n", joueur_suivant(joueur));
            }
        }
    }
    gagnant(grille);
}


// Simule une partie ordinateur contre ordinateur

void computer_vs_computer(){
    int joueur = 1;
    int ligne, colonne;

    // Choix de la strategie des joueurs "computer"
    int strategie1 = 0;
    int strategie2 = 0;
    // Stratégie du joueur 1
    while ((strategie1 != 1) && (strategie1 != 2)){
        printf("\nQuelle strategie souhaitez-vous utiliser pour le joueur ordinateur 1 ?\n1 = naif\n2 = minimax\n");
        scanf("\n%d", &strategie1);
        switch(strategie1){
            case 1 :
                break;
            case 2 :
                break;
            default :
            printf("\nStrategie non reconnue\n");
        }
    }
    // Stratégie du joueur 2
    while ((strategie2 != 1) && (strategie2 != 2)){
        printf("\nQuelle strategie souhaitez-vous utiliser pour le joueur ordinateur 2 ?\n1 = naif\n2 = minimax\n");
        scanf("\n%d", &strategie2);
        switch(strategie2){
            case 1 :
                break;
            case 2 :
                break;
            default :
            printf("\nStrategie non reconnue\n");
        }
    }

    // Initialisation de la grille
    int grille[N][N];
    initialisation_grille(grille);
    printf("\nDebut de la partie\n");
    affiche_grille(grille);
    printf("\nJoueur 1 : 0 point\nJoueur 2 : 0 point\n");

    // Partie machine vs machine
    while(!partie_finie(grille)){
        if (joueur == 1){
            if (strategie1 == 1){
                strategie_naive(grille, &ligne, &colonne, joueur);
            }
            else{
                strategie_minimax(grille, &ligne, &colonne, joueur, 1, 0);
            }
            jouer(grille, ligne, colonne, joueur);
            affiche_grille(grille);
            score(grille);
            if (peut_jouer(grille, joueur_suivant(joueur))){
                joueur = joueur_suivant(joueur);
            }
            else {
                printf("\nLe joueur %d passe son tour\n", joueur_suivant(joueur));
            }
        }
        else {
            if (strategie2 == 1){
                strategie_naive(grille, &ligne, &colonne, joueur);
            }
            else{
                strategie_minimax(grille, &ligne, &colonne, joueur, 1, 0);
            }
            jouer(grille, ligne, colonne, joueur);
            affiche_grille(grille);
            score(grille);
            if (peut_jouer(grille, joueur_suivant(joueur))){
                joueur = joueur_suivant(joueur);
            }
            else {
                printf("\nLe joueur %d passe son tour\n", joueur_suivant(joueur));
            }
        }
    }
    gagnant(grille);
}


// Permet d'etudier le nombre de victoires d'un joueur selon sa strategie

int computer_vs_computer_stat(){
    int joueur = 1;
    int ligne, colonne;

    // Initialisation de la grille
    int grille[N][N];
    initialisation_grille(grille);

    // Partie machine vs machine
    while(!partie_finie(grille)){
        if (joueur == 1){
            strategie_minimax(grille, &ligne, &colonne, joueur, 1, 0);
            jouer(grille, ligne, colonne, joueur);
            if (peut_jouer(grille, joueur_suivant(joueur))){
                joueur = joueur_suivant(joueur);
                //score(grille);
            }
        }
        else {
            strategie_minimax(grille, &ligne, &colonne, joueur, 1, 0);
            jouer(grille, ligne, colonne, joueur);
            if (peut_jouer(grille, joueur_suivant(joueur))){
                joueur = joueur_suivant(joueur);
                //score(grille);
            }
        }
    }
    return gagnant_stat(grille);
}
