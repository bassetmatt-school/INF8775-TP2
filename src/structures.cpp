#include <cmath>
#include <numeric>
#include "structures.hpp"

int distance(Point const p1, Point const p2) {
	Point v = p1 - p2;
	return std::round(std::sqrt(v.x * v.x + v.y * v.y));
}


int OptimalSet::countElements() const {
	return std::popcount<uint32_t>(this->elements);
}

bool OptimalSet::isInSet(int i) const {
	return this->elements & (1 << i);
}

void OptimalSet::toggleFromSet(int i) {
	this->elements ^= (1 << i);
}
