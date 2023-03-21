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

Node::Node(uint idx, std::vector<Node*> children){
	this->index = idx;
	this->children = children;
}

void build_tree(std::vector<edge> const& edges, Node& tree) {
	std::map<int, Node*> already_added;

	id_node first_node(0, &tree);
	already_added.insert(first_node);
	for (edge e : edges) {
		Node* new_node = new Node(e.second, std::vector<Node*>());
		id_node new_entry(e.second, new_node);
		already_added.insert(new_entry);
		if (already_added.contains(e.first))
			already_added.at(e.first)->children.push_back(new_node);
	}
}
