#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*
 * Initialise toute la grille avec des cellules mortes.
 * Chaque case est remplie par le caractère espace.
 */
void initialiser_grille(int largeur, int hauteur, char grille[hauteur][largeur])
{
	int ligne;
	int colonne;

	ligne = 0;
	while (ligne < hauteur)
	{
		colonne = 0;
		while (colonne < largeur)
		{
			grille[ligne][colonne] = ' ';
			colonne++;
		}
		ligne++;
	}
}

/*
 * Affiche la grille dans le terminal.
 * Chaque ligne est imprimée puis un retour à la ligne est ajouté.
 */
void afficher_grille(int largeur, int hauteur, char grille[hauteur][largeur])
{
	int ligne;
	int colonne;

	ligne = 0;
	while (ligne < hauteur)
	{
		colonne = 0;
		while (colonne < largeur)
		{
			putchar(grille[ligne][colonne]);
			colonne++;
		}
		putchar('\n');
		ligne++;
	}
}

/*
 * Compte le nombre de voisins vivants autour d'une cellule donnée.
 * On explore les 8 cases adjacentes autour de la position (ligne, colonne).
 */
int compter_voisins(int largeur, int hauteur, char grille[hauteur][largeur], int ligne, int colonne)
{
	int nombre_voisins = 0;
	int deplacement_ligne;
	int deplacement_colonne;
	int nouvelle_ligne;
	int nouvelle_colonne;

	deplacement_ligne = -1;
	while (deplacement_ligne <= 1)
	{
		deplacement_colonne = -1;
		while (deplacement_colonne <= 1)
		{
			nouvelle_ligne = ligne + deplacement_ligne;
			nouvelle_colonne = colonne + deplacement_colonne;
			if (!(deplacement_colonne == 0 && deplacement_ligne == 0)
				&& nouvelle_ligne >= 0 && nouvelle_ligne < hauteur
				&& nouvelle_colonne >= 0 && nouvelle_colonne < largeur
				&& grille[nouvelle_ligne][nouvelle_colonne] == '0')
				nombre_voisins++;
			deplacement_colonne++;
		}
		deplacement_ligne++;
	}
	return (nombre_voisins);
}

/*
 * Programme principal.
 * Il lit les paramètres de la ligne de commande, traite les commandes du stylo,
 * puis applique les règles du jeu de la vie pendant le nombre d'itérations demandé.
 */
int main(int argc, char *argv[])
{
	int largeur;
	int hauteur;
	int iterations;
	int stylo_x;
	int stylo_y;
	int stylo_levé;
	char caractere;

	if (argc != 4)
	{
		fprintf(stderr, "Usage: %s width height iterations\n", argv[0]);
		return (1);
	}

	largeur = atoi(argv[1]);
	hauteur = atoi(argv[2]);
	iterations = atoi(argv[3]);
	stylo_x = 0;
	stylo_y = 0;
	stylo_levé = 1;

	if (largeur <= 0 || hauteur <= 0)
		return (1);

	char grille[hauteur][largeur];
	char grille_suivante[hauteur][largeur];

	initialiser_grille(largeur, hauteur, grille);
	initialiser_grille(largeur, hauteur, grille_suivante);

	while (read(0, &caractere, 1) > 0)
	{
		if (caractere == 'w')
		{
			if (stylo_y > 0)
			{
				stylo_y--;
				if (stylo_levé == 0)
					grille[stylo_y][stylo_x] = '0';
			}
		}
		else if (caractere == 'a')
		{
			if (stylo_x > 0)
			{
				stylo_x--;
				if (stylo_levé == 0)
					grille[stylo_y][stylo_x] = '0';
			}
		}
		else if (caractere == 's')
		{
			if (stylo_y < hauteur - 1)
			{
				stylo_y++;
				if (stylo_levé == 0)
					grille[stylo_y][stylo_x] = '0';
			}
		}
		else if (caractere == 'd')
		{
			if (stylo_x < largeur - 1)
			{
				stylo_x++;
				if (stylo_levé == 0)
					grille[stylo_y][stylo_x] = '0';
			}
		}
		else if (caractere == 'x')
		{
			stylo_levé = !stylo_levé;
			if (stylo_levé == 0)
				grille[stylo_y][stylo_x] = '0';
		}
	}

	int generation;
	int ligne;
	int colonne;
	int voisins;
	char cellule;

	generation = 0;
	while (generation < iterations)
	{
		ligne = 0;
		while (ligne < hauteur)
		{
			colonne = 0;
			while (colonne < largeur)
			{
				voisins = compter_voisins(largeur, hauteur, grille, ligne, colonne);
				cellule = grille[ligne][colonne];

				if (cellule == '0' && voisins < 2)
					grille_suivante[ligne][colonne] = ' ';
				else if (cellule == '0' && (voisins == 2 || voisins == 3))
					grille_suivante[ligne][colonne] = '0';
				else if (cellule == '0' && voisins > 3)
					grille_suivante[ligne][colonne] = ' ';
				else if (cellule == ' ' && voisins == 3)
					grille_suivante[ligne][colonne] = '0';
				else
					grille_suivante[ligne][colonne] = grille[ligne][colonne];
				colonne++;
			}
			ligne++;
		}

		ligne = 0;
		while (ligne < hauteur)
		{
			colonne = 0;
			while (colonne < largeur)
			{
				grille[ligne][colonne] = grille_suivante[ligne][colonne];
				colonne++;
			}
			ligne++;
		}
		generation++;
	}

	//printf("\n=== Simulation Result (%d iterations) ===\n", iterations);
	afficher_grille(largeur, hauteur, grille);

	return (0);
}
