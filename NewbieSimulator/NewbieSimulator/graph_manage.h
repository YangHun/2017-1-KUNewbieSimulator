#pragma once
#include"graph_structure.h"

extern void parse_graph(Graph_structure* result);
extern void free_graph_structure(Graph_structure* target);
extern void print_graph(Graph_structure* target);
extern void make_edge_objects(Graph_structure* target);
extern void make_vertex_objects(Graph_structure* target, object_t*** map_button_ptr);
