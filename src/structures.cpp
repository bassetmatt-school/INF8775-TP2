#include <cmath>
#include <cassert>
#include <numeric>
#include "structures.hpp"

int distance(Point const p1, Point const p2) {
	Point v = p1 - p2;
	return std::round(std::sqrt(v.x * v.x + v.y * v.y));
}

bool contains(Set s, int i) {
	return s & (1 << i);
}

Set add(Set s, int i) {
	assert(!contains(s, i));
	return s | (1 << i);
}

Set remove(Set s, int i) {
	assert(contains(s, i));
	return s ^ (1 << i);
}

int size(Set s) {
	return std::popcount<uint32_t>(s);
}

Set initSet(int i) {
	uint32_t set = 0;
	for (int j = 1; j < i; set |= (1 << j++)) {}
	return set;
}

Set get_set(Path p) {
	return (uint32_t) p;
}

uint8_t get_point(Path p) {
	return (uint8_t) (p >> 32);
}

Path path_from_point(uint8_t pt) {
	return (uint64_t) pt << 32;
}

Path constr(uint8_t pt, uint32_t set) {
	return set + ((uint64_t) pt << 32);
}
