int main(int ac, char **av)
{
    if (ac != 4)
        return (1);

    // variables
    int largeur = atoi(av[1]);
    int hauteur = atoi(av[2]);
    int nb_gen = atoi(av[3]);
    
    // protection
    if (largeur <= 0 || hauteur <= 0)
        return (1);

    // tableau + init
    char tab[hauteur][largeur];
    char tab2[hauteur][largeur];

    int i = 0;
    int j = 0;
    while (i < hauteur)
    {
        j = 0;
        while (j < largeur)
        {
            tab[i][j] = ' ';
            j++;
        }
        i++;
    }
    i = 0;
    j = 0;
    while (i < hauteur)
    {
        j = 0;
        while (j < largeur)
        {
            tab[i][j] = ' ';
            j++;
        }
        i++;
    }

    // read stylo
    int stylo_x = 0;
    int stylo_y = 0;
    int stylo_leve = -1;
    char c;
    while (read(0, &c, 1) > 0)
    {
        if (c == 'w')
        {
            if (stylo_y > 0)
            {
                stylo_y--;
                if (stylo_leve == 1)
                    tab[stylo_y][stylo_x] = '0';
            }
        }
        if (c == 'a')
        {
            if (stylo_x > 0)
            {
                stylo_x--;
                if (stylo_leve == 1)
                    tab[stylo_y][stylo_x] = '0';
            }
        }
        if (c == 's')
        {
            if (stylo_y < hauteur - 1)
            {
                stylo_y++;
                if (stylo_leve == 1)
                    tab[stylo_y][stylo_x] = '0';
            }
        }
        if (c == 'd')
        {
            if (stylo_x < largeur - 1)
            {
                stylo_y++;
                if (stylo_leve == 1)
                    tab[stylo_y][stylo_x] = '0';
            }
        }
        if (c == 'c')
        {
            stylo_leve *= -1;
             if (stylo_leve == 1)
                tab[stylo_y][stylo_x] = '0';
        }
    }

    // generation
    int gen = 0;
    i = 0;
    j = 0;
    int voisin = 0;
    char cell;
    while (gen < nb_gen)
    {
        j = 0;
        while ()
        {}
        i++;
    }
}