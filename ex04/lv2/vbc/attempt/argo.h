#ifndef ARGO_H
# define ARGO_H

# include <stddef.h>
# include <stdio.h>

// The three data types we are required to parse
typedef enum
{
	INTEGER,
	STRING,
	MAP
}						type_t;

// Forward declarations so the structs can reference each other
typedef struct s_json	json;
typedef struct s_pair	pair;
typedef struct s_map	map;

// The map structure holding an array of key-value pairs
struct					s_map
{
	pair				*data;
	size_t				size;
};

// A single key-value pair inside a map
struct					s_pair
{
	char				*key;
	json				value;
};

// The core JSON node. It holds a type identifier and the corresponding data.
struct					s_json
{
	type_t				type;
	int					integer;
	char				*string;
	map					*map;
};

// The main function prototype
int						argo(json *dst, FILE *stream);

#endif
