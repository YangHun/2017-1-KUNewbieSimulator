#pragma once

#include <stdbool.h>

typedef enum vertex_type{
	VERTEX_TYPE_NONE,
	VERTEX_TYPE_BUILDING,
	VERTEX_TYPE_BUSROUTE,
	VERTEX_TYPE_ECOUNT,
}vertex_type;

typedef struct Coord_2D {
	int x;
	int y;
} Coord_2D;

typedef struct vertex {
	Coord_2D loc;
	vertex_type type;
	union {
		struct {
			int id;
		} as_busroute;
	} value;
	char name[32];
} vertex;

typedef struct edge {
	int vertexindex_1;
	int vertexindex_2;
	float length;
	bool reversed;
	char group[32];
} edge;

typedef struct Graph_structure {
	vertex* vertexArray;
	edge* edgeArray;
	int *edges_sorted_args;
	int Num_of_Vertex;
	int Num_of_Edge;
} Graph_structure;
