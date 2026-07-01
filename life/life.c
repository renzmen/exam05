#include "life.h"

void free_map(t_map *map)
{
    if (!map)
        return;
    for (int x = 0; x < map->rows; x++)
        free(map->matrix[x]);
    free(map->matrix);
    free(map);
}

void print_map(t_map *map)
{
    for (int i = 0; i < map->rows; i++)
    {
        for (int j = 0; j < map->cols; j++)
            putchar(map->matrix[i][j]);
        putchar('\n');
    }
}

// Conta i vicini vivi direttamente nella matrice senza rischiare sfasamenti
int count_neighbors(t_map *map, int r, int c)
{
    int alive = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;
            int nb_r = r + i;
            int nb_c = c + j;
            if (nb_r >= 0 && nb_r < map->rows && nb_c >= 0 && nb_c < map->cols)
            {
                if (map->matrix[nb_r][nb_c] == '0')
                    alive++;
            }
        }
    }
    return alive;
}

// Gestisce l'evoluzione di una singola iterazione usando una matrice temporanea di supporto
void step_simulation(t_map *map)
{
    char **next = malloc(sizeof(char *) * map->rows);
    if (!next)
        return;
        
    for (int i = 0; i < map->rows; i++)
    {
        next[i] = malloc(sizeof(char) * map->cols);
        for (int j = 0; j < map->cols; j++)
        {
            int alive = count_neighbors(map, i, j);
            if (map->matrix[i][j] == '0')
            {
                if (alive == 2 || alive == 3)
                    next[i][j] = '0';
                else
                    next[i][j] = ' ';
            }
            else
            {
                if (alive == 3)
                    next[i][j] = '0';
                else
                    next[i][j] = ' ';
            }
        }
    }

    // Ricopia i dati aggiornati nella matrice originale
    for (int i = 0; i < map->rows; i++)
    {
        for (int j = 0; j < map->cols; j++)
            map->matrix[i][j] = next[i][j];
        free(next[i]);
    }
    free(next);
}

int main(int c, char **v)
{
    if (c != 4)
        return 1;

    // Buffer statico capiente per leggere lo stdin in sicurezza senza crash di realloc
    char string[8192];
    int len = 0;
    char d;
    
    while (len < 8191 && read(0, &d, 1) > 0)
    {
        string[len] = d;
        len++;
    }
    string[len] = '\0';

    t_map *map = malloc(sizeof(t_map));
    if (!map)
        return 1;

    map->cols = atoi(v[1]);
    map->rows = atoi(v[2]);
    map->iterations = atoi(v[3]);
    
    if (map->cols <= 0 || map->rows <= 0)
    {
        free(map);
        return 1;
    }

    map->matrix = malloc(sizeof(char *) * map->rows);
    for (int x = 0; x < map->rows; x++)
    {
        map->matrix[x] = malloc(sizeof(char) * map->cols);
        for (int y = 0; y < map->cols; y++)
            map->matrix[x][y] = ' ';
    }

    int pen = 0;
    int i = 0;
    int j = 0;
    
    for (int k = 0; string[k]; k++)
    {
        char b = string[k];
        if (b == 'x')
        {
            pen = !pen;
            if (pen)
                map->matrix[i][j] = '0';
        }
        else if (b == 'w' || b == 's' || b == 'a' || b == 'd')
        {
            if (b == 'w' && i > 0) i--;
            else if (b == 's' && i < map->rows - 1) i++;
            else if (b == 'a' && j > 0) j--;
            else if (b == 'd' && j < map->cols - 1) j++;
            
            if (pen)
                map->matrix[i][j] = '0';
        }
        // I restanti caratteri (\r, \n, spazi) vengono scartati e ignorati in automatico
    }

    while (map->iterations > 0)
    {
        step_simulation(map);
        map->iterations--;
    }

    print_map(map);
    free_map(map);
    return 0;
}