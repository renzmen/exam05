#ifndef BSQ_H
# define BSQ_H


# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>


typedef struct {
    int rows;
    int cols;
    char empty;
    char obstacle;
    char full;
    char **map;
} t_map;


// Parsing
int     parse_first_line(char *line, t_map *map);
int     read_map(FILE *fp, t_map *map);


// Algoritmo principale
void    bsq(t_map *map);


// Utility (eventuale)
void    free_map(t_map *map);


#endif
