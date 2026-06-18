#ifndef LIFE_H
#define LIFE_H

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

// Prototipi se dividi in più file, altrimenti basta questo
#endif