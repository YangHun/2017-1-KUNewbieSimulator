#include"engine.h"
#include"graph_structure.h"
//----------------------------------         //
//Button, map moving setting By hasu & minkyu//
//----------------------------------         //

extern void map_button_on_click_listener_func(object_t *o);
int compare(const void *a, const void *b);
void print_graph(Graph_structure* target);

void parse_graph(Graph_structure* result) {
	int vertex_count;
	int vertex_name;
	int edge_count;
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
		fscanf(map_location, "%d %d", &result->vertexArray[i].loc.x, &result->vertexArray[i].loc.y);
	}


	fscanf(map_location, "%d", &vertex_name);
	for (int i = 0; i < vertex_name; i++)
	{
		int n = 0;
		fscanf(map_location, "%d %s", &n, &result->vertexArray[n].name);
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
		result->edgeArray[i + edge_count].vertexindex_1 = ver2;
		result->edgeArray[i + edge_count].vertexindex_2 = ver1;
		result->edgeArray[i + edge_count].length = length;
	}
	qsort((result->edgeArray), 2 * edge_count, sizeof(edge), compare);
	
}

int compare(const void *a, const void *b)    // 오름차순 비교 함수 구현
{
	edge num1 = *(edge *)a;    // void 포인터를 int 포인터로 변환한 뒤 역참조하여 값을 가져옴
	edge num2 = *(edge *)b;    // void 포인터를 int 포인터로 변환한 뒤 역참조하여 값을 가져옴

	if (num1.vertexindex_1 != num2.vertexindex_1) {
		return num1.vertexindex_1 - num2.vertexindex_1;
	}
	else {
		return num1.vertexindex_2 - num2.vertexindex_2;
	}
}

void free_graph_structure(Graph_structure* target) {
	free(target->edgeArray);
	free(target->vertexArray);
}

void register_button_to_vertex(Graph_structure* target, object_t*** map_button_ptr) { // vertex 갯수만큼 stack 오름
	*map_button_ptr = (object_t**)malloc(sizeof(object_t *) * target->Num_of_Vertex);
	for (int i = 0; i < target->Num_of_Vertex; i++)
	{
		object_t temp = create_object("Resources\\UI\\routegame\\v_building.png",target->vertexArray[i].loc.x - 15, target->vertexArray[i].loc.y - 15);
		ui_set_button(&temp);
		ui_set_on_click_listener(&temp, map_button_on_click_listener_func);
		Stack.push(&Stack, temp);
		(*map_button_ptr)[i] = &Stack.objs[Stack.counter - 1];
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

