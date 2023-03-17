#include <cmath>
#include "point.hpp"

int distance(Point const p1, Point const p2) {
	Point v = p1 - p2;
	return std::round(std::sqrt(v.x * v.x + v.y * v.y));
}
