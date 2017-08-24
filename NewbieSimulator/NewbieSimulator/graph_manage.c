#include"engine.h"
#include"graph_structure.h"
#include "graph_manage.h"
#include "stringSwitch.h"
//----------------------------------         //
//Button, map moving setting By hasu & minkyu//
//----------------------------------         //

extern void map_button_on_click_listener_func(object_t *o);
static int graph_edge_argcompare_totalorder(const void *a, const void *b);
static int graph_edge_argcompare_firstonly(const void *a, const void *b);
static int graph_edge_refcompare_totalorder(const void *a, const void *b);
static int graph_edge_refcompare_firstonly(const void *a, const void *b);

static Graph_structure *current_graph;

void parse_graph(Graph_structure* result) {
	int vertex_count;
	int vertex_name_count;
	int edge_count;
	int edge_grp_count;
	int ver1, ver2;
	float length;

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
		vertex *v = &result->vertexArray[i];
		fscanf(map_location, "%d %d", &v->loc.x, &v->loc.y);
		v->type = VERTEX_TYPE_NONE;
	}


	fscanf(map_location, "%d", &vertex_name_count);
	for (int i = 0; i < vertex_name_count; i++)
	{
		int n = 0;
		char buf[64];
		fscanf(map_location, "%d %s", &n, buf);
		vertex *v = &result->vertexArray[n];

		if (strncmp(buf, "b/", 2) == 0) {
			v->type = VERTEX_TYPE_BUILDING;
			strncpy(v->name, buf + 2, strlen(buf + 2) + 1);
		}
		else if (strncmp(buf, "br/", 3) == 0) {
			v->type = VERTEX_TYPE_BUSROUTE;
			int c;
			sscanf(buf + 3, "%d%n", &v->value.as_busroute.id, &c);
			strncpy(v->name, buf + c + 4, strlen(buf + c + 4) + 1);
		}
	}

	fscanf(map_location, "%d", &edge_count);
	result->Num_of_Edge = edge_count;
	result->edgeArray = (edge*)malloc(sizeof(edge) * edge_count * 2);
	
	for (int i = 0; i < edge_count; i++)
	{
		fscanf(map_location, "%d %d %f", &ver1, &ver2, &length);
		result->edgeArray[i].vertexindex_1 = ver1;
		result->edgeArray[i].vertexindex_2 = ver2;
		result->edgeArray[i].length = length;
		result->edgeArray[i].reversed = false;
		result->edgeArray[i].grpid = 0;
		result->edgeArray[i + edge_count].vertexindex_1 = ver2;
		result->edgeArray[i + edge_count].vertexindex_2 = ver1;
		result->edgeArray[i + edge_count].length = length;
		result->edgeArray[i + edge_count].reversed = true;
		result->edgeArray[i].grpid = 0;
	}

	fscanf(map_location, "%d", &edge_grp_count);
	for (int i = 0; i < edge_grp_count; i++)
	{
		int n = 0;
		fscanf(map_location, "%d ", &n);
		edge *e = &result->edgeArray[n];
		fscanf(map_location, "%d", &e->grpid);
	}

	result->edges_sorted_args = malloc(sizeof(int) * edge_count * 2);
	for (int i = 0; i < edge_count * 2; i++) {
		result->edges_sorted_args[i] = i;
	}
	current_graph = result;
	qsort(result->edges_sorted_args, 2 * edge_count, sizeof(int), graph_edge_argcompare_totalorder);
	current_graph = NULL;

	for (int i = 0; i < vertex_count; i++)
	{
		vertex *v = &result->vertexArray[i];
		if (v->name != NULL) {
			v->roomID = getRoomMessage_little_change(v->name);
		}
		else {
			v->roomID = ROOM_DEFAULT;
		}
	}
	for (int i = 0; i < vertex_count; i++)
	{
		vertex *v = &result->vertexArray[i];
		
	}
}

int graph_edge_argcompare_totalorder(const void *a, const void *b)
{
	int i = *(int *)a;
	int j = *(int *)b;

	edge num1 = current_graph->edgeArray[i];
	edge num2 = current_graph->edgeArray[j];

	if (num1.vertexindex_1 != num2.vertexindex_1) {
		return num1.vertexindex_1 - num2.vertexindex_1;
	}
	else {
		return num1.vertexindex_2 - num2.vertexindex_2;
	}
}

int graph_edge_argcompare_firstonly(const void *a, const void *b)
{
	int i = *(int *)a;
	int j = *(int *)b;

	edge num1 = current_graph->edgeArray[i];
	edge num2 = current_graph->edgeArray[j];

	return num1.vertexindex_1 - num2.vertexindex_1;
}

int graph_edge_refcompare_totalorder(const void *a, const void *b)
{
	int i = *(int *)a;
	int j = *(int *)b;

	edge num1 = current_graph->edgeArray[current_graph->edges_sorted_args[i]];
	edge num2 = current_graph->edgeArray[current_graph->edges_sorted_args[j]];

	printf("num1: %d %d\n", num1.vertexindex_1, num1.vertexindex_2);
	printf("num2: %d %d\n", num2.vertexindex_1, num2.vertexindex_2);

	if (num1.vertexindex_1 != num2.vertexindex_1) {
		return num1.vertexindex_1 - num2.vertexindex_1;
	}
	else {
		return num1.vertexindex_2 - num2.vertexindex_2;
	}
}

int graph_edge_refcompare_firstonly(const void *a, const void *b)
{
	int i = *(int *)a;
	int j = *(int *)b;

	edge num1 = current_graph->edgeArray[current_graph->edges_sorted_args[i]];
	edge num2 = current_graph->edgeArray[current_graph->edges_sorted_args[j]];

	return num1.vertexindex_1 - num2.vertexindex_1;
}

void free_graph_structure(Graph_structure* target) {
	free(target->edgeArray);
	free(target->vertexArray);
}

void make_edge_objects(Graph_structure* target) {
	extern ALLEGRO_COLOR edge_color_default;
	for (int i = 0; i < target->Num_of_Edge; i++)
	{
		edge e = target->edgeArray[i];
		vertex *u = &target->vertexArray[e.vertexindex_1];
		vertex *v = &target->vertexArray[e.vertexindex_2];
		object_t o = create_line_object(edge_color_default, u->loc.x, u->loc.y, v->loc.x, v->loc.y, 5.0);
		Stack.push(&Stack, o);
	}
}

void make_vertex_objects(Graph_structure* target, object_t*** map_button_ptr) { // vertex 갯수만큼 stack 오름
	*map_button_ptr = (object_t**)malloc(sizeof(object_t *) * target->Num_of_Vertex);
	for (int i = 0; i < target->Num_of_Vertex; i++)
	{
		vertex *v = &target->vertexArray[i];
		const char *paths[VERTEX_TYPE_ECOUNT] = {
			"Resources\\UI\\routegame\\v_default.png",
			"Resources\\UI\\routegame\\v_building.png",
			"Resources\\UI\\routegame\\v_busstop.png",
		};
		const char *path = paths[v->type];
		if (v->type == VERTEX_TYPE_BUSROUTE && strcmp(v->name, "", 1) == 0)
		{
			path = paths[VERTEX_TYPE_NONE];
		}
		object_t temp = create_object(path, v->loc.x - 15, v->loc.y - 15);
		ui_set_button(&temp);
		ui_set_on_click_listener(&temp, map_button_on_click_listener_func);
		Stack.push(&Stack, temp);
		(*map_button_ptr)[i] = &Stack.objs[Stack.counter - 1];
	}
}

void print_graph(Graph_structure* target) {
	for (int i = 0; i < target->Num_of_Vertex; i++) {
		printf("%d %d %d \n", target->vertexArray[i].loc.x, target->vertexArray[i].loc.y, target->vertexArray[i].roomID);
	}
	printf("\n");
	for (int i = 0; i < target->Num_of_Edge * 2; i++) {
		if (target->edgeArray[target->edges_sorted_args[i]].vertexindex_1 == 104 && target->edgeArray[target->edges_sorted_args[i]].vertexindex_2 == 103)
		{
			printf("*** %d %d %d\n", i, target->edges_sorted_args[i], 254);
		}
		printf("%d %d %d\n", target->edgeArray[target->edges_sorted_args[i]].vertexindex_1, target->edgeArray[target->edges_sorted_args[i]].vertexindex_2, target->edgeArray[target->edges_sorted_args[i]].length);
	}
}

