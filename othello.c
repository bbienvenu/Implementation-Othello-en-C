#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "othello.h"


// Fonction "random" (genere des nombres aleatoires entre 0 et n-1)

int my_rand(int n)
{
   static int first = 0;

   if (first == 0)
   {
    // permet d'initialiser le générateur de nombres aléatoires (la fonction rand)
      srand (time (NULL));
      first = 1;
   }
   return (rand ()%n);
}


// Initialise la grille en placant les 4 premiers pions

void initialsation_grille(int grille[N][N]){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            grille[i][j] = 0;
        }
    }
    grille[(N/2)-1][(N/2)-1] = noir;
    grille[N/2][N/2] = noir;
    grille[N/2][(N/2)-1] = blanc;
    grille[(N/2)-1][N/2] = blanc;
}


// Affiche la grille passee en argument

void affiche_grille(int grille[N][N]){
    printf("\n");
    for(int ligne = 0; ligne < N; ligne++){
        printf("%d.  ", ligne);
        for(int colonne = 0; colonne < N; colonne++){
            printf("%d  ", grille[ligne][colonne]);
        }
        printf("\n");
    }
    printf("\n    0. 1. 2. 3. 4. 5. 6. 7.\n");
}


// Renvoie True si on joue une case de la grille, False sinon

int case_valide(int ligne, int colonne){
    return ((ligne >= 0 && ligne < N) && (colonne >= 0 && colonne < N));
}


// Renvoie True si la case jouee est vide

int case_vide(int grille[N][N], int ligne, int colonne){
    return grille[ligne][colonne] == 0;
}


// Verifie si le coup (i, j) est valide pour la direction "verticale haut"

int verticale_haut(int grille[N][N], int ligne, int colonne, int joueur){
    int joueur_adverse=joueur_suivant(joueur);
    int i = ligne - 1;
    if (grille[i][colonne] == joueur){
        return 0;
    }
    while(case_valide(i, colonne) && grille[i][colonne] == joueur_adverse){
        i--;
    }
    if (case_valide(i, colonne) && grille[i][colonne] == joueur){
        return 1;
    }
    return 0;
}


// Verifie si le coup (i, j) est valide pour la direction "verticale bas"

int verticale_bas(int grille[N][N], int ligne, int colonne, int joueur){
    int joueur_adverse=joueur_suivant(joueur);
    int i = ligne + 1;
    if (grille[i][colonne] == joueur){
        return 0;
    }
    while(case_valide(i, colonne) && grille[i][colonne] == joueur_adverse){
        i++;
    }
    if (case_valide(i, colonne) && grille[i][colonne] == joueur){
        return 1;
    }
    return 0;
}


// Verifie si le coup (i, j) est valide pour la direction "horizontale gauche"

int horizontale_gauche(int grille[N][N], int ligne, int colonne, int joueur){
    int joueur_adverse=joueur_suivant(joueur);
    int j = colonne - 1;
    if (grille[ligne][j] == joueur){
        return 0;
    }
    while(case_valide(ligne, j) && grille[ligne][j] == joueur_adverse){
        j--;
    }
    if (case_valide(ligne, j) && grille[ligne][j] == joueur){
        return 1;
    }
    return 0;
}


// Verifie si le coup (i, j) est valide pour la direction "horizontale droite"

int horizontale_droite(int grille[N][N], int ligne, int colonne, int joueur){
    int joueur_adverse=joueur_suivant(joueur);
    int j = colonne + 1;
    if (grille[ligne][j] == joueur){
        return 0;
    }
    while(case_valide(ligne, j) && grille[ligne][j] == joueur_adverse){
        j++;
    }
    if (case_valide(ligne, j) && grille[ligne][j] == joueur){
        return 1;
    }
    return 0;
}


// Verifie si le coup (i, j) est valide pour la direction "diagonale haut droite"

int diagonale_haut_droite(int grille[N][N], int ligne, int colonne, int joueur){
    int joueur_adverse=joueur_suivant(joueur);
    int i = ligne - 1;
    int j = colonne + 1;
    if (grille[i][j] == joueur){
        return 0;
    }
    while(case_valide(i, j) && grille[i][j] == joueur_adverse){
        j++;
    i--;
    }
    if (case_valide(i, j) && grille[i][j] == joueur){
        return 1;
    }
    return 0;
}


// Verifie si le coup (i, j) est valide pour la direction "diagonale haut gauche"

int diagonale_haut_gauche(int grille[N][N], int ligne, int colonne, int joueur){
    int joueur_adverse=joueur_suivant(joueur);
    int i = ligne - 1;
    int j = colonne - 1;
    if (grille[i][j] == joueur){
        return 0;
    }
    while(case_valide(i, j) && grille[i][j] == joueur_adverse){
        j--;
    i--;
    }
    if (case_valide(i, j) && grille[i][j] == joueur){
        return 1;
    }
    return 0;
}


// Verifie si le coup (i, j) est valide pour la direction "diagonale bas droite"

int diagonale_bas_droite(int grille[N][N], int ligne, int colonne, int joueur){
    int joueur_adverse=joueur_suivant(joueur);
    int i = ligne + 1;
    int j = colonne + 1;
    if (grille[i][j] == joueur){
        return 0;
    }
    while(case_valide(i, j) && grille[i][j] == joueur_adverse){
        j++;
    i++;
    }
    if (case_valide(i, j) && grille[i][j] == joueur){
        return 1;
    }
    return 0;
}


// Verifie si le coup (i, j) est valide pour la direction "diagonale bas gauche"

int diagonale_bas_gauche(int grille[N][N], int ligne, int colonne, int joueur){
    int joueur_adverse=joueur_suivant(joueur);
    int i = ligne + 1;
    int j = colonne - 1;
    if (grille[i][j] == joueur){
        return 0;
    }
    while(case_valide(i, j) && grille[i][j] == joueur_adverse){
        j--;
    i++;
    }
    if (case_valide(i, j) && grille[i][j] == joueur){
        return 1;
    }
    return 0;
}


// Verifie que le coup (i, j) est valide (peut être joué)

int coup_valide(int grille[N][N], int ligne, int colonne, int joueur){
    if (!case_valide(ligne, colonne) || !case_vide(grille, ligne, colonne)){
        return 0;
    }
    return verticale_bas(grille,ligne,colonne,joueur)||verticale_haut(grille,ligne,colonne,joueur)||horizontale_droite(grille,ligne,colonne,joueur)||horizontale_gauche(grille,ligne,colonne,joueur)||diagonale_bas_droite(grille,ligne,colonne,joueur)||diagonale_bas_gauche(grille,ligne,colonne,joueur)||diagonale_haut_droite(grille,ligne,colonne,joueur)||diagonale_haut_gauche(grille,ligne,colonne,joueur);
}


// Etant donné une configuration de la grille, verifie si le joueur (actuel) peut jouer

int peut_jouer(int grille[N][N], int joueur){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (coup_valide(grille, i, j, joueur)){
                return 1;
            }
        }
    }
    return 0;
}


// Determine le joueur suivant (etant donné le joueur actuel)

int joueur_suivant(int joueur){
    return (joueur % 2) + 1;
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


// Verifie si la partie est terminee

int partie_finie(int grille[N][N]){
    if ((peut_jouer(grille,noir) || peut_jouer(grille,blanc))){
        return 0;
    }
    return 1;
}


// Determine le gagnant d'une partie terminee (etant donné une grille finale)

void gagnant(int grille[N][N]){
    int nb_noir = 0;
    int nb_blanc = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if (grille[i][j] == 1){
                nb_noir++;
            }
            else if (grille[i][j]==2){
                nb_blanc++;
            }
        }
    }
    if (nb_noir > nb_blanc){
        printf("\nLe joueur 1 gagne!\n");
    }
    else if (nb_noir < nb_blanc){
        printf("\nLe joueur 2 gagne !\n");
    }
    else{
        printf("\nC'est un match nul !\n");
    }
}


// Etant donné une grille, calcule le score des deux joueurs

void score(int grille[N][N]){
    int nb_noir = 0;
    int nb_blanc = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if (grille[i][j] == 1){
                nb_noir++;
            }
            else if (grille[i][j]==2){
                nb_blanc++;
            }
        }
    }
    printf("\nJoueur 1 : %d points\nJoueur 2 : %d points", nb_noir, nb_blanc);
}


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


// Simule une partie entre deux joueurs (non machine)

void partie_2_joueurs(){
    int joueur = 1;
    int ligne, colonne;

    // Initialisation de la grille
    int grille[N][N];
    initialsation_grille(grille);
    affiche_grille(grille);

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


//Simule une partie entre un joueur et l'ordinateur

void partie_vs_computer(){
    int joueur = 1;
    int ligne, colonne;

    // Initialisation de la grille
    int grille[N][N];
    initialsation_grille(grille);
    affiche_grille(grille);

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
            ligne = rand()%8;
            colonne = rand()%8;
            while(!coup_valide(grille,ligne,colonne,joueur)){
                ligne = rand()%8;
                colonne = rand()%8;
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

void strategie_naive(int grille[N][N],int * ligne,int * colonne,int joueur){
    *ligne = my_rand(8);
    *colonne = my_rand(8);
    while(!coup_valide(grille,*ligne,*colonne,joueur)){
        //srand(time(NULL));
        *ligne = my_rand(8);
        *colonne =my_rand(8);
    }
}

// Simule une partie ordinateur contre ordinateur

void computer_vs_computer(){
    int joueur = 1;
    int ligne, colonne;

    // Initialisation de la grille
    int grille[N][N];
    initialsation_grille(grille);
    affiche_grille(grille);
    
    // Partie machine vs machine
    while(!partie_finie(grille)){
        if (joueur == 1){
            strategie_naive(grille,&ligne,&colonne,joueur);
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
            strategie_naive(grille,&ligne,&colonne,joueur);
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
