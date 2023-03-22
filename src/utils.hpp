#ifndef TP2_UTILS_HEADER
#define TP2_UTILS_HEADER

#include <vector>
#include <string>
#include "structures.hpp"
enum Algos{
	GREEDY,
	DP,
	APPROX,
};

int load_file(std::string const& filename, std::vector<Point>& p_list);

void sort_order(std::vector<int>& order);

#endif // !TP2_UTILS_HEADER
