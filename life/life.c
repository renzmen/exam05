#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


typedef struct s_map
{
    int cols;
    int rows;
    int iterations;
    char **matrix;
} t_map;


t_map *new_map(t_map *map)
{
    t_map *new = malloc(sizeof(t_map));
    if (!new)
        return NULL;
    new->rows = map->rows + 2;
    new->cols = map->cols + 2;
    new->matrix = malloc(sizeof(char *) * new->rows);
    if (!new->matrix)
        return NULL;
    for (int x = 0; x < new->rows; x++)
    {
        new->matrix[x] = malloc(sizeof(char) * new->cols);
        for (int y = 0; y < new->cols; y++)
        {
            if (x == 0 || y == 0 || x == new->rows - 1 || y == new->cols - 1)
                new->matrix[x][y] = ' ';
            else
                new->matrix[x][y] = map->matrix[x - 1][y - 1];
        }
    }
    return new;
}


void free_map(t_map *map)
{
    if (!map)
        return;
    for (int x = 0; x < map->rows; x++)
        free(map->matrix[x]);
    free(map->matrix);
    free(map);
}


void destiny(t_map *map, t_map *new)
{
    int alive = 0;
    for (int i = 1; i < new->rows - 1; i++)
    {
        for (int j = 1; j < new->cols - 1; j++)
        {
            alive = 0;
            if (new->matrix[i - 1][j - 1] == '0')
                alive++;
            if (new->matrix[i][j - 1] == '0')
                alive++;
            if (new->matrix[i + 1][j - 1] == '0')
                alive++;
            if (new->matrix[i + 1][j] == '0')
                alive++;
            if (new->matrix[i + 1][j + 1] == '0')
                alive++;
            if (new->matrix[i][j + 1] == '0')
                alive++;
            if (new->matrix[i - 1][j + 1] == '0')
                alive++;
            if (new->matrix[i - 1][j] == '0')
                alive++;
            if (new->matrix[i][j] == '0' && (alive == 2 || alive == 3))
                map->matrix[i - 1][j - 1] = '0';
            else if (new->matrix[i][j] == '0' && (alive < 2 || alive > 3))
                map->matrix[i - 1][j - 1] = ' ';
            else if (new->matrix[i][j] == ' ' && alive == 3)
                map->matrix[i - 1][j - 1] = '0';
            else
                map->matrix[i - 1][j - 1] = ' ';
        }
    }
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


int main(int c, char **v)
{
    if (c != 4)
    {
        write(2, "3 arguments required\n", 21);
        return 1;
    }
    char *string = malloc(1);
    int len = 0;
    char d;
    while (read(0, &d, 1) > 0)
    {
        string[len] = d;
        len++;
        string = realloc(string, len + 1);
    }
    string[len] = '\0';
    t_map *map = malloc(sizeof(t_map));
    if (!map)
        return 1;
    map->cols = 0;
    map->rows = 0;
    map->iterations = 0;
    map->matrix = NULL;


    map->cols = atoi(v[1]);
    map->rows = atoi(v[2]);
    map->iterations = atoi(v[3]);
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
        }
        else if (b == 'w' && i > 0)
            i--;
        else if (b == 's' && i < map->rows - 1)
            i++;
        else if (b == 'a' && j > 0)
            j--;
        else if (b == 'd' && j < map->cols - 1)
            j++;
        else
            continue;
        if (pen)
            map->matrix[i][j] = '0';
    }
    while (map->iterations > 0)
    {
        t_map *new = new_map(map);
        destiny(map, new);
        free_map(new);
        map->iterations--;
    }
    print_map(map);
    free_map(map);
    free(string);
    return 0;
}
