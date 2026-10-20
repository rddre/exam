#include <stdio.h>
#include <stdlib.h>

void bsq(FILE *file)
{
    int hauteur_attendue;
    char vide, obs, plein;

    // 1. Lire la première ligne (ex: "9 . o x")
    if (fscanf(file, "%d %c %c %c", &hauteur_attendue, &vide, &obs, &plein) != 4)
    {
        fputs("map error\n", stderr);
        return;
    }

    // TODO: Checker ici si hauteur_attendue <= 0, ou si caractères en double/non-imprimables

    char *line = NULL;
    size_t cap = 0;
    
    // Avaler le '\n' qui traîne après le fscanf
    getline(&line, &cap, file); 

    // static évite le crash mémoire (stack overflow) d'un tableau géant
    static char tab[9999][9999]; 
    int hauteur = 0;
    int largeur = 0;

    // 2. Lire le fichier ligne par ligne
    while (getline(&line, &cap, file) != -1)
    {
        // Mesurer la taille de la ligne lue en ignorant le '\n'
        int len = 0;
        while (line[len] != '\0' && line[len] != '\n')
            len++;

        // La toute première ligne fixe la largeur de référence
        if (hauteur == 0)
            largeur = len;
        // Si une ligne suivante n'a pas la même taille, on arrête
        else if (len != largeur)
        {
            // TODO: Gérer l'erreur proprement
            break; 
        }

        // Copier la ligne dans tab (sans le '\n')
        for (int j = 0; j < largeur; j++)
        {
            tab[hauteur][j] = line[j];
        }

        hauteur++;
    }
    free(line); // Toujours libérer ce que getline a utilisé

    // ------------------------------------------------------------------
    // À PARTIR D'ICI :
    // 1. 'tab' est rempli. 
    // 2. 'hauteur' contient le nombre de lignes réellement lues.
    // 3. 'largeur' contient le nombre de colonnes.
    //
    // TODO : Vérifier que hauteur == hauteur_attendue
    // TODO : Vérifier que tab ne contient QUE 'vide' ou 'obs'
    // TODO : Trouver le plus grand carré
    // TODO : Imprimer la map résolue
    // ------------------------------------------------------------------
}

int main(int ac, char **av)
{
    // Si pas d'argument, lire sur l'entrée standard (stdin)
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
            // Saut de ligne obligatoire entre chaque résultat de carte
            if (ac > 2 && i < ac - 1)
                fprintf(stdout, "\n");
        }
    }
    return 0;
}