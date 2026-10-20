#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>

// trouver le plus petit des 3 voisins (haut, gauche, diagonale)
int min(int a, int b, int c)
{
    int m = a;
    if (b < m)
        m = b;
    if (c < m)
        m = c;
    return m;
}

void bsq(FILE *file)
{
    int hauteur = 0;
    char vide, obs, plein;

    // 1. lire la 1ere ligne (ex: 9 . o x)
    if (fscanf(file, "%d %c %c %c", &hauteur, &vide, &obs, &plein) != 4)
    {
        fputs("map error\n", stderr);
        return;
    }

    // check les variables de la 1ere ligne
    if (hauteur <= 0 || vide == obs || vide == plein || obs == plein)
    {
        fputs("map error\n", stderr);
        return;
    }
    if (vide < 32 || vide > 126 || obs < 32 || obs > 126 || plein < 32 || plein > 126)
    {
        fputs("map error\n", stderr);
        return;
    }

    char *line = NULL;
    size_t cap = 0;

    // avaler le '\n' qui reste apres fscanf
    if (getline(&line, &cap, file) == -1 || line[0] != '\n')
    {
        free(line);
        fputs("map error\n", stderr);
        return;
    }

    // 2. lire la premiere vraie ligne de la map pour connaitre la largeur
    int len = getline(&line, &cap, file);
    if (len <= 0 || (hauteur > 1 && line[len - 1] != '\n'))
    {
        free(line);
        fputs("map error\n", stderr);
        return;
    }

    int largeur = len;
    if (line[len - 1] == '\n')
        largeur--;
    if (largeur == 0)
    {
        free(line);
        fputs("map error\n", stderr);
        return;
    }
    int tab[hauteur][largeur];

    int max_size = 0;
    int best_y = 0;
    int best_x = 0;

    // 3. remplir tout le tab ligne par ligne
    for (int i = 0; i < hauteur; i++)
    {
        // pour i > 0, on lit la ligne suivante (la ligne 0 est deja lue)
        if (i > 0)
        {
            len = getline(&line, &cap, file);
            if (len <= 0 || (i < hauteur - 1 && line[len - 1] != '\n'))
            {
                free(line);
                fputs("map error\n", stderr);
                return;
            }
            int current_width = len;
            if (line[len - 1] == '\n')
                current_width--;
            if (current_width != largeur)
            {
                free(line);
                fputs("map error\n", stderr);
                return;
            }
        }

        // parcourir les colonnes de la ligne
        for (int j = 0; j < largeur; j++)
        {
            if (line[j] != vide && line[j] != obs)
            {
                free(line);
                fputs("map error\n", stderr);
                return;
            }

            if (line[j] == obs)
                tab[i][j] = 0;
            else
            {
                // si on est sur le bord (haut ou gauche), max carre = 1
                if (i == 0 || j == 0)
                    tab[i][j] = 1;
                else
                    tab[i][j] = min(tab[i - 1][j], tab[i][j - 1], tab[i - 1][j - 1]) + 1;

                // garder le plus grand carre
                if (tab[i][j] > max_size)
                {
                    max_size = tab[i][j];
                    best_y = i;
                    best_x = j;
                }
            }
        }
    }

    // verifier qu'il n'y a pas de lignes en trop dans le fichier
    if (getline(&line, &cap, file) != -1)
    {
        free(line);
        fputs("map error\n", stderr);
        return;
    }
    free(line);

    // 4. print le tab final
    for (int i = 0; i < hauteur; i++)
    {
        for (int j = 0; j < largeur; j++)
        {
            // si on est dans la zone du meilleur carre
            if (i > best_y - max_size && i <= best_y && j > best_x - max_size && j <= best_x)
                fprintf(stdout, "%c", plein);
            else if (tab[i][j] == 0)
                fprintf(stdout, "%c", obs);
            else
                fprintf(stdout, "%c", vide);
        }
        fprintf(stdout, "\n");
    }
}

int main(int ac, char **av)
{
    // si pas d'argument, lire sur l'entree standard (stdin)
    if (ac == 1)
        bsq(stdin);
    else
    {
        for (int i = 1; i < ac; i++)
        {
            FILE *file = fopen(av[i], "r");
            if (!file)
                fputs("map error\n", stderr);
            else
            {
                bsq(file);
                fclose(file);
            }
            // saut de ligne entre chaque map si plusieurs fichiers
            if (ac > 2 && i < ac - 1)
                fprintf(stdout, "\n");
        }
    }
    return 0;
}