#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int ac, char **av)
{
    // protection ac
    if (ac != 4)
        return 1;

    // declarer variable atoi
    int largeur = atoi(av[1]);
    int hauteur = atoi(av[2]);
    int nb_gen = atoi(av[3]);

    // check var
    if (largeur <= 0 || hauteur <= 0 || nb_gen < 0)
        return 1;

    // declarer tap et pen
    int tab[2][hauteur + 2][largeur + 2];
    int x = 1;
    int y = 1;
    int pen = 0;
    char c;

    // init tab
    for (int b = 0; b <= 1; b++)
        for (int i = 0; i < hauteur + 2; i++)
            for (int j = 0; j < largeur + 2; j++)
                tab[b][i][j] = 0;

    // read pen
    while (read(0, &c, 1) > 0)
    {
        if (c == 'w' && y > 1)
            y--;
        if (c == 's' && y < hauteur)
            y++;
        if (c == 'a' && x > 1)
            x--;
        if (c == 'd' && x < largeur)
            x++;
        if (c == 'x')
            pen = !pen;

        if (pen == 1)
            tab[0][y][x] = 1;
    }

    //generation
    for (int gen = 0; gen < nb_gen; gen++)
    {
        int cur = gen % 2;
        int next  = (gen + 1) % 2;
        for (int i = 1; i <= hauteur; i++)
        {
            for (int j = 1; j <= largeur; j++)
            {
                int voisin = 0;
                for (int dy = -1; dy <= 1; dy++)
                {
                    for (int dx = -1; dx <= 1; dx++)
                    {
                        if (dy != 0 || dx != 0)
                            voisin += tab[cur][dy+i][dx+j];
                    }
                }
                if (tab[cur][i][j] == 1)
                    tab[next][i][j] = (voisin == 3 || voisin == 2);
                else
                    tab[next][i][j] = (voisin == 3);
            }
        }
    }

    // choisir le tab final
    int final = nb_gen % 2;

    // print tab
    for (int i = 1; i <= hauteur; i++)
    {
        for (int j = 1; j <= largeur; j++)
        {
            if (tab[final][i][j] == 1)
                putchar('O');
            else
                putchar(' ');
        }
        putchar('\n');
    }
}