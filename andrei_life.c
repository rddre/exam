#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    if (ac != 4)
        return (1);

    // initialiser tout
    int largeur = atoi(av[1]);
    int hauteur = atoi(av[2]);
    int nb_gen = atoi(av[3]);

    if (largeur <= 0 ||  hauteur <= 0 || nb_gen < 0)
        return (1);

    int x = 1;
    int y = 1;
    int pen = 0;
    int tab[2][hauteur+2][largeur+2];
    int c;

    // initialiser les 2 arbres
    for(int b=0; b < 2; b++)
        for(int i=0; i < hauteur + 2; i++)
            for(int j=0; j < largeur + 2; j++)
                tab[b][i][j]=0;
        
    // capter le stylo

    while (read(0, &c, 1) > 0)
    {
        if (c == 'w' && y > 1)
            y--;
        else if (c == 's' && y < hauteur)
            y++;
        else if (c == 'a' && x > 1)
            x--;
        else if (c == 'd' && x < largeur)
            x++;
        else if (c == 'x')
            pen = !pen;
        if (pen)
            tab[0][y][x] = 1;
    }

    // la genration

    for (int gen = 0; gen < nb_gen; gen++)
    {
        int cur = gen % 2;
        int next = (gen + 1) % 2;
        for (int i = 1; i <= hauteur; i++)
        {
            for (int j = 1; j <= largeur; j++)
            {
                int voisin = 0;
                for (int dy = -1; dy <= 1; dy++)
                {
                    for (int dx = -1; dx <= 1; dx++)
                    {
                        if (dx != 0 || dy != 0)
                            voisin += tab[cur][dy+i][dx+j];
                    }
                }
                if (tab[cur][i][j]==1)
                    tab[next][i][j] = (voisin == 2 || voisin == 3);
                else
                    tab[next][i][j] = (voisin == 3);
            }
        }
    }

    // dire quel tab on print
    int final = nb_gen % 2;

    // print le final
    for (int i = 1; i <= hauteur; i++)
    {
        for (int j = 1; j <= largeur; j++)
        {
            if (tab[final][i][j])
                putchar('O');
            else
                putchar(' ');
        }
        putchar('\n');
    }
}