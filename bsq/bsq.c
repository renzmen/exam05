#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// Definizione della struttura come nel tuo bsq.h
typedef struct {
    int rows;
    int cols;
    char empty;
    char obstacle;
    char full;
    char **map;
} t_map;

static int ft_strlen(const char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

static char *ft_strdup(const char *s)
{
    int len = ft_strlen(s);
    char *copy = malloc(sizeof(char) * (len + 1));
    if (!copy)
        return NULL;
    for (int i = 0; i < len; i++)
        copy[i] = s[i];
    copy[len] = '\0';
    return copy;
}

static int ft_atoi(const char *s)
{
    int n = 0;
    for (int i = 0; s[i] >= '0' && s[i] <= '9'; i++)
        n = n * 10 + (s[i] - '0');
    return n;
}

// VARIATO: Gestione flessibile degli spazi per rispecchiare l'esempio "9 . o x"
int parse_first_line(char *line, t_map *map)
{
    int i = 0;
    while (line[i] >= '0' && line[i] <= '9')
        i++;
    if (i == 0)
        return -1;
    
    char *num = malloc(sizeof(char) * (i + 1));
    if (!num)
        return -1;
    for (int j = 0; j < i; j++)
        num[j] = line[j];
    num[i] = '\0';
    map->rows = ft_atoi(num);
    free(num);
    
    if (map->rows <= 0)
        return -1;

    // VARIATO: Invece di fare line[i], line[i+1], line[i+2] in modo rigido,
    // saltiamo i caratteri di spaziatura (' ' o '\t') come richiesto dal testo.
    while (line[i] == ' ' || line[i] == '\t') i++;
    if (line[i] == '\0' || line[i] == '\n') return -1;
    map->empty = line[i++];

    while (line[i] == ' ' || line[i] == '\t') i++;
    if (line[i] == '\0' || line[i] == '\n') return -1;
    map->obstacle = line[i++];

    while (line[i] == ' ' || line[i] == '\t') i++;
    if (line[i] == '\0' || line[i] == '\n') return -1;
    map->full = line[i++];

    if (map->empty == map->obstacle || map->empty == map->full || map->obstacle == map->full)
        return -1;
    return 0;
}

void free_map(t_map *map)
{
    if (map->map)
    {
        for (int i = 0; i < map->rows; i++)
        {
            if (map->map[i])
                free(map->map[i]);
        }
        free(map->map);
        map->map = NULL;
    }
}

int read_map(FILE *fp, t_map *map)
{
    map->map = malloc(sizeof(char *) * map->rows);
    if (!map->map)
        return -1;
    for (int i = 0; i < map->rows; i++)
        map->map[i] = NULL;
        
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int row = 0;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (read > 0 && line[read - 1] == '\n')
            line[read - 1] = '\0';

        if (row >= map->rows) {
            free(line);
            free_map(map);
            return -1;
        }

        if (row == 0) {
            map->cols = ft_strlen(line);
            if (map->cols <= 0) {
                free(line);
                free_map(map);
                return -1;
            }
        }

        if (ft_strlen(line) != map->cols) {
            free_map(map);
            free(line);
            return -1;
        }

        for (int k = 0; k < map->cols; k++) {
            if (line[k] != map->empty && line[k] != map->obstacle) {
                free_map(map);
                free(line);
                return -1;
            }
        }

        map->map[row] = ft_strdup(line);
        if (!map->map[row]) {
            free_map(map);
            free(line);
            return -1;
        }
        row++;
    }

    free(line);
    if (row != map->rows) {
        free_map(map);
        return -1;
    }
    return 0;
}

void bsq(t_map *map)
{
    int **dp = calloc(map->rows, sizeof(int *));
    if (!dp) return;
    
    for (int i = 0; i < map->rows; i++) {
        dp[i] = calloc(map->cols, sizeof(int));
        if (!dp[i]) {
            for (int j = 0; j < i; j++) free(dp[j]);
            free(dp);
            return;
        }
    }

    int max_size = 0, max_i = 0, max_j = 0;

    for (int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->cols; j++) {
            if (map->map[i][j] == map->obstacle)
                dp[i][j] = 0;
            else if (i == 0 || j == 0)
                dp[i][j] = 1;
            else {
                int min = dp[i - 1][j];
                if (dp[i][j - 1] < min) min = dp[i][j - 1];
                if (dp[i - 1][j - 1] < min) min = dp[i - 1][j - 1];
                dp[i][j] = 1 + min;
            }
   // Il tuo confronto con '>' è perfetto: garantisce che, a parità di dimensione,
  // rimanga valido il primo trovato (quello più in alto e più a sinistra).
            if (dp[i][j] > max_size) {
                max_size = dp[i][j];
                max_i = i;
                max_j = j;
            }
        }
    }

    for (int i = max_i; i > max_i - max_size; i--) {
        for (int j = max_j; j > max_j - max_size; j--) {
            map->map[i][j] = map->full;
        }
    }

    for (int i = 0; i < map->rows; i++) {
        fputs(map->map[i], stdout);
        fputs("\n", stdout);
    }

    for (int i = 0; i < map->rows; i++) free(dp[i]);
    free(dp);
    free_map(map);
}

// VARIATO: Creata questa funzione per evitare la duplicazione del codice del main.
// Riceve un descrittore di file (che sia stdin o un file aperto con fopen).
// VARIATO: Tutti i messaggi di errore ora stampano rigorosamente "map error\n" su stderr.
int process_stream(FILE *fp)
{
    t_map map;
    char *line = NULL;
    size_t len = 0;

    map.map = NULL;
    if (getline(&line, &len, fp) == -1) {
        fputs("map error\n", stderr);
        return -1;
    }
    if (parse_first_line(line, &map) == -1) {
        fputs("map error\n", stderr);
        free(line);
        return -1;
    }
    free(line);

    if (read_map(fp, &map) == -1) {
        fputs("map error\n", stderr);
        return -1;
    }

    bsq(&map);
    return 0;
}

int main(int argc, char **argv)
{
    // Caso 1: Nessun argomento -> Legge da Standard Input
    if (argc < 2) {
        process_stream(stdin);
        return 0;
    }

    // VARIATO: Rimosso il blocco "if(c == 2)" che conteneva errori di sintassi.
    // VARIATO: Implementato un ciclo 'for' che permette di gestire n argomenti (più mappe di fila).
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (!fp) {
            fputs("map error\n", stderr); // VARIATO: corretto il testo dell'errore
            continue; // VARIATO: ora il 'continue' è dentro un ciclo legittimo, quindi compila!
        }
        process_stream(fp);
        fclose(fp);
    }
    return 0;
}