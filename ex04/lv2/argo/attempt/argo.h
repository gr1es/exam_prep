#ifndef ARGO_H
# define ARGO_H

# include <stdio.h>
# include <stddef.h>

typedef enum {
    INTEGER,
    STRING,
    MAP
} type_t;

typedef struct s_json json;
typedef struct s_pair pair;
typedef struct s_map map;

struct s_map {
    pair    *data;
    size_t  size;
};

struct s_json {
    type_t  type;
    int     integer;
    char    *string;
    map     *map;
};

struct s_pair {
    char    *key;
    json    value;
};

int argo(json *dst, FILE *stream);

#endif
