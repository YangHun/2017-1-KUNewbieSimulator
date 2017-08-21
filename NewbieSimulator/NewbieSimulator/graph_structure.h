#pragma once

#include <stdbool.h>

typedef struct Coord_2D {
	int x;
	int y;
} Coord_2D;

typedef struct vertex {
	Coord_2D loc;
	char name[10];
} vertex;

typedef struct edge {
	int vertexindex_1;
	int vertexindex_2;
	float length;
	bool reversed;
} edge;

typedef struct Graph_structure {
	vertex* vertexArray;
	edge* edgeArray;
	int *edges_sorted_args;
	int Num_of_Vertex;
	int Num_of_Edge;
} Graph_structure;
