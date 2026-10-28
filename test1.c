#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int ac, char **av)
{
    // protection ac
    if (ac != 4)
        return 1;

    // declarer 3 var
    int largeur = atoi(av[1]);
    int hauteur = atoi(av[2]);
    int nb_gen = atoi(av[3]);

    // check 3 var
    if (largeur <= 0 || hauteur <= 0 || nb_gen < 0)
        return 1;

    // declarer tab pen x y c
    int tab[2][hauteur + 2][largeur + 2];
    int x = 1;
    int y = 1;
    int pen = 0;
    char c;

    // init tab
    for (int b = 0; b <= 1; b++)
        for (int i = 0; i <= (hauteur); i++)
            for (int j = 0 <= (largeur + 2); j++)
                tab[b][i][j] = 0;

    // read pen
    while (read())

    // generation

    // final tab

    // print tab
}