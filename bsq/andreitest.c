#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>

// trouver plus petit des voisin haut gauche diagonale
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
    char vide, obs, plain;

    // lire la 1er ligne
    if (fscanf(file, "%d %c %c %c", &hauteur, &vide, &obs, &plain) != 4)
    {
        fputs("map error\n", stderr);
        return;
    }

    // check les var
    if (hauteur < 1 || vide == obs || vide == plain || obs == plain)
    {
        fputs("map error\n", stderr);
        return;
    }
    if (vide < 32 || vide > 126 || obs < 32 || obs > 126 || plain < 32 || plain > 126)
    {
        fputs("map error\n", stderr);
        return;
    }

    // getline pour le \n laisser par fscanf
    char *line = NULL;
    size_t cap = 0;

    if (getline(&line, &cap, file) == -1 || line[0] != '\n')
    {
        free(line);
        fputs("map error\n", stderr);
        return;
    }


    // lire la ligne 1
    int len = getline(&line, &cap, file);
    if (len < 1 || line[len - 1] != '\n')
    {
        free(line);
        fputs("map error\n", stderr);
        return;
    }

    // declarer largeur et check
    int largeur = len - 1;
    if (largeur == 0)
    {
        free(line);
        fputs("map error\n", stderr);
        return;
    }

    // decalrer tab max size best y et x
    int tab[hauteur][largeur];
    int max_size = 0;
    int best_y = 0;
    int best_x = 0;

    // boucle principale
    for (int i = 0; i < hauteur; i++)
    {
        // i > 0, on lance getline au 2eme passage dans la boucle
        if (i > 0)
        {
            int len = getline(&line, &cap, file);
            if (len < 1 || line[len - 1] != '\n')
            {
                free(line);
                fputs("map error\n", stderr);
                return;
            }
            len--;
            if (len != largeur)
            {
                free(line);
                fputs("map error\n", stderr);
                return;
            }
        } 

        // check les cologne
        for (int j = 0; j < largeur; j++)
        {
            // check caractere
            if (line[j] != vide && line[j] != obs)
            {
                free(line);
                fputs("map error\n", stderr);
                return;
            }

            // obs = skip
            if (line[j] == obs)
                tab[i][j] = 0;
            else
            {
                // premiere caractere de la map = carre = 1 si non addition
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

    // verifier ligne en trop
    if (getline(&line, &cap, file) != -1)
    {
        free(line);
        fputs("map error\n", stderr);
        return;
    }
    free(line);

    // print tab
    for (int i = 0; i < hauteur; i++)
    {
        for (int j = 0; j < largeur; j++)
        {
            if (i > best_y - max_size && i <= best_y && j > best_x - max_size && j <= best_x)
                fprintf(stdout, "%c", plain);
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
    if (ac == 1)
        bsq(stdin);
    else
    {
        for (int nb_file = 1; nb_file < ac; nb_file++)
        {
            FILE *file = fopen(av[nb_file], "r");
            if (!file)
                fputs("map error\n", stderr);
            else
            {
                bsq(file);
                fclose(file);
            }
            if (ac > 2 && nb_file < ac - 1)
                fprintf(stdout, "\n");
        }
    }


    return 0;
}