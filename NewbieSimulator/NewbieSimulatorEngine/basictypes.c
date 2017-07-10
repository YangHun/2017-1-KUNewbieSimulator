#include "basictyps.h"

bool positioni_equals(positioni_t a, positioni_t b) {
	return a.x == b.x && a.y == b.y;
}

bool rect_contains_point(rect_t rect, positioni_t point) {
	return (
		(rect.left <= point.x) &&
		(rect.top <= point.y) &&
		(point.x < rect.left + rect.width) &&
		(point.y < rect.top + rect.height)
	);
}