#include <stdlib.h>
#include <stdio.h>

void erreur(void)
{
	fputs("map error\n", stderr);
}

int caractere_imprimable(char caractere)
{
	return (caractere >= 32 && caractere <= 126);
}

int doublon(char a, char b, char c)
{
	return (a == b || a == c || b == c);
}

int minimum(int a, int b, int c)
{
	int plus_petit;

	plus_petit = a;
	if (b < plus_petit)
		plus_petit = b;
	if (c < plus_petit)
		plus_petit = c;
	return (plus_petit);
}

void afficher_resultat(int nombre_lignes, int largeur, int tableau[nombre_lignes][largeur], char vide, char obstacle, char plein, int taille_max, int meilleur_y, int meilleur_x)
{
	int ligne;
	int colonne;

	printf("\n=== BSQ Result ===\n");
	ligne = 0;
	while (ligne < nombre_lignes)
	{
		colonne = 0;
		while (colonne < largeur)
		{
			if (ligne > meilleur_y - taille_max && ligne <= meilleur_y
				&& colonne > meilleur_x - taille_max && colonne <= meilleur_x)
				putchar(plein);
			else if (tableau[ligne][colonne] == 0)
				putchar(obstacle);
			else
				putchar(vide);
			colonne++;
		}
		putchar('\n');
		ligne++;
	}
}

void traiter_carte(FILE *fichier)
{
	char ligne[4096];
	char vide;
	char obstacle;
	char plein;
	int nombre_lignes;
	int largeur;
	int ligne_actuelle;
	int colonne;
	int taille_max;
	int meilleur_y;
	int meilleur_x;
	int longueur_ligne;
	int voisins;
	int i;
	int j;

	if (fscanf(fichier, "%d %c %c %c", &nombre_lignes, &vide, &obstacle, &plein) != 4)
	{
		erreur();
		return ;
	}
	if (nombre_lignes < 1 || doublon(vide, obstacle, plein)
		|| !caractere_imprimable(vide) || !caractere_imprimable(obstacle) || !caractere_imprimable(plein))
	{
		erreur();
		return ;
	}
	if (fgets(ligne, sizeof(ligne), fichier) == NULL)
	{
		erreur();
		return ;
	}
	if (fgets(ligne, sizeof(ligne), fichier) == NULL)
	{
		erreur();
		return ;
	}

	longueur_ligne = 0;
	while (ligne[longueur_ligne] != '\n' && ligne[longueur_ligne] != '\0')
	{
		if (ligne[longueur_ligne] != vide && ligne[longueur_ligne] != obstacle)
		{
			erreur();
			return ;
		}
		longueur_ligne++;
	}
	if (longueur_ligne == 0)
	{
		erreur();
		return ;
	}
	largeur = longueur_ligne;

	char carte[nombre_lignes][largeur];
	int tableau[nombre_lignes][largeur];

	colonne = 0;
	while (colonne < largeur)
	{
		carte[0][colonne] = ligne[colonne];
		if (ligne[colonne] == vide)
			tableau[0][colonne] = 1;
		else
			tableau[0][colonne] = 0;
		colonne++;
	}

	ligne_actuelle = 1;
	while (ligne_actuelle < nombre_lignes)
	{
		if (fgets(ligne, sizeof(ligne), fichier) == NULL)
		{
			erreur();
			return ;
		}
		longueur_ligne = 0;
		while (ligne[longueur_ligne] != '\n' && ligne[longueur_ligne] != '\0')
		{
			if (ligne[longueur_ligne] != vide && ligne[longueur_ligne] != obstacle)
			{
				erreur();
				return ;
			}
			longueur_ligne++;
		}
		if (longueur_ligne != largeur)
		{
			erreur();
			return ;
		}
		colonne = 0;
		while (colonne < largeur)
		{
			carte[ligne_actuelle][colonne] = ligne[colonne];
			if (ligne[colonne] == vide)
				tableau[ligne_actuelle][colonne] = 1;
			else
				tableau[ligne_actuelle][colonne] = 0;
			colonne++;
		}
		ligne_actuelle++;
	}

	taille_max = 0;
	meilleur_y = 0;
	meilleur_x = 0;
	ligne_actuelle = 1;
	while (ligne_actuelle < nombre_lignes)
	{
		colonne = 1;
		while (colonne < largeur)
		{
			if (carte[ligne_actuelle][colonne] == vide)
			{
				voisins = minimum(tableau[ligne_actuelle - 1][colonne],
					tableau[ligne_actuelle][colonne - 1],
					tableau[ligne_actuelle - 1][colonne - 1]);
				tableau[ligne_actuelle][colonne] = voisins + 1;
				if (tableau[ligne_actuelle][colonne] > taille_max)
				{
					taille_max = tableau[ligne_actuelle][colonne];
					meilleur_y = ligne_actuelle;
					meilleur_x = colonne;
				}
			}
			else
				tableau[ligne_actuelle][colonne] = 0;
			colonne++;
		}
		ligne_actuelle++;
	}

	if (taille_max == 0)
	{
		i = 0;
		while (i < nombre_lignes)
		{
			j = 0;
			while (j < largeur)
			{
				if (carte[i][j] == vide)
				{
					taille_max = 1;
					meilleur_y = i;
					meilleur_x = j;
					break;
				}
				j++;
			}
			if (taille_max == 1)
				break;
			i++;
		}
	}
	if (taille_max == 0 && nombre_lignes > 0 && largeur > 0)
	{
		taille_max = 1;
		meilleur_y = 0;
		meilleur_x = 0;
	}
	afficher_resultat(nombre_lignes, largeur, tableau, vide, obstacle, plein, taille_max, meilleur_y, meilleur_x);
}

int main(int argc, char *argv[])
{
	FILE *fichier;
	int i;

	if (argc == 1)
		traiter_carte(stdin);
	else
	{
		i = 1;
		while (i < argc)
		{
			fichier = fopen(argv[i], "r");
			if (!fichier)
				erreur();
			else
			{
				traiter_carte(fichier);
				fclose(fichier);
			}
			i++;
		}
	}
	return (0);
}
