#pragma once

#include <stdbool.h>

struct positioni_t;
typedef struct positioni_t positioni_t;
struct positioni_t {
	int x;
	int y;
};

bool positioni_equals(positioni_t a, positioni_t b);

struct positionf_t;
typedef struct positionf_t position_t;
struct positionf_t {
	float x;
	float y;
};

struct rect_t;
typedef struct rect_t rect_t;
struct rect_t {
	int left;
	int top;
	int width;
	int height;
};

bool rect_contains_point(rect_t rect, positioni_t point);
