#include <stdio.h>
#include <stdlib.h>

void bsq(FILE *file)
{
    int hauteur_give;
    int hauteur;
    int largeur;
    char vide;
    char obs;
    char plain;

    // lire premiere ligne
    if (fscanf(file, "%d %c %c %c", &hauteur_give, &vide, &obs, &plain) != 4)
    {
        fputs("map error\n", stderr);
        return;
    }

    char *line = NULL;
    size_t cap = 0;

    getline(&line, &cap, file);

    static char tab[5000][5000];
    int hauteur = 0;
    int largeur = 0;
    while (getline(&line, &cap, file) != -1)
    {
        int len = 0;
        while (line[len] != '\n')
    }
}

int main(int ac, char **av)
{
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
            if (ac > 2 && i < ac - 1)
                fprintf(stdout, "\n");
        }
    }
    return 0;
}