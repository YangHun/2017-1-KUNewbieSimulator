#pragma once
#include"graph_structure.h"
void parse_graph(Graph_structure* result);
void free_graph_structure(Graph_structure* target);
void print_graph(Graph_structure* target);
void register_button_to_vertex(Graph_structure* target, map_button_ptr* map_button, _button* map_button_on_click_listener);
