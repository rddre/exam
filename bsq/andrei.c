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

    // check les var

    // getline pour le \n a la fin

    // lire la ligne 1
    int len = getline();

    // declarer largeur et check
    int largeur = len;

    // decalrer tab max size best y et x

    // boucle principale
    for (int i = 0; i < hauteur; i++)
    {
        // i > 0, on lance getline au 2eme passage dans la boucle
        if (i > 0)
        {

        } 

        // check les cologne
        for (int j = 0; j < largeur; j++)
        {
            // check caractere

            // obs = skip
            if (line[j] == obs)
                tab[i][j] = 0;
            else
            {
                // premiere caractere de la map = carre = 1
                // sinon envoi a min

                // garder le plus grand carre

            }
        }
    }

    // verifier ligne en trop

    // print tab

}

int main(int ac, char **av)
{
    if (ac == 1)
        bsq(stdin);
    else
    {
        for (int nb_file = 1; nb_file < ac; nb_file++)
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