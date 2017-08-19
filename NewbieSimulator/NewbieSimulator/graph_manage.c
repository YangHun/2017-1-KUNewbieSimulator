#include"engine.h"
#include"graph_structure.h"
//----------------------------------         //
//Button, map moving setting By hasu & minkyu//
//----------------------------------         //

void map_button_on_click_listener_func();

void parse_graph(Graph_structure* result) {
	int vertex_count;
	int edge_count;
	int ver1, ver2;

	FILE* map_location;
	if ((map_location = fopen("Resources\\UI\\routegame\\map_location.txt", "r")) == NULL)
	{
		printf("map_location.txt file read error\n");
		return -1;
	}
	
	fscanf(map_location, "%d", &vertex_count);
	result->Num_of_Vertex = vertex_count;
	result->vertexArray = (vertex*)malloc(sizeof(vertex) * vertex_count);
	

	for (int i = 0; i < vertex_count; i++)
	{
		fscanf(map_location, "%d %d", &result->vertexArray[i].loc.x, &result->vertexArray[i].loc.y);
	}

	fscanf(map_location, "%d", &edge_count);
	result->Num_of_Edge = edge_count;
	result->edgeArray = (edge*)malloc(sizeof(edge) * edge_count);
	
	for (int i = 0; i < edge_count; i++)
	{
		fscanf(map_location, "%d %d", &ver1, &ver2);
		result->edgeArray[i].vertexindex_1 = ver1;
		result->edgeArray[i].vertexindex_2 = ver2;
		result->edgeArray[i].length = 1.0;
	}
}

void free_graph_structure(Graph_structure* target) {
	free(target->edgeArray);
	free(target->vertexArray);
}

void register_button_to_vertex(Graph_structure* target, map_button_ptr* map_button, _button* map_button_on_click_listener) {
	map_button = (map_button_ptr*)malloc(sizeof(map_button_ptr) * target->Num_of_Vertex);
	map_button_on_click_listener = (_button*)malloc(sizeof(_button) * target->Num_of_Vertex);
	for (int i = 0; i < target->Num_of_Vertex; i++)
	{
		object_t temp = create_colored_object(al_map_rgb(255, 255, 255), 10, 10, target->vertexArray[i].loc.x, target->vertexArray[i].loc.y);
		map_button_on_click_listener[i] = map_button_on_click_listener_func;
		ui_set_on_click_listener(&temp, map_button_on_click_listener[i]);
		Stack.push(&Stack, temp);
		map_button[i].button = &Stack.objs[Stack.counter - 1];
	}
}

void print_graph(Graph_structure* target) {
	for (int i = 0; i < target->Num_of_Vertex; i++) {
		printf("%d %d \n", target->vertexArray[i].loc.x, target->vertexArray[i].loc.y);
	}
	printf("\n");
	for (int i = 0; i < target->Num_of_Edge; i++) {
		printf("%d %d %d\n", target->edgeArray[i].vertexindex_1, target->edgeArray[i].vertexindex_2, target->edgeArray[i].length);
	}
	printf("\n");
}

void map_button_on_click_listener_func()
{
}