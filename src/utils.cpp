#include <fstream>
#include "utils.hpp"

int load_file(std::string const& filename, std::vector<Point>& p_list){
	std::ifstream file_stream(filename);
	if (!file_stream.is_open()) {
		std::cout << "Couldn't open file\n";
		return -1;
	}

	int N;
	file_stream >> N;
	p_list.reserve(N);
	while (file_stream) {
		int x, y;
		file_stream >> x >> y;
		p_list.push_back(Point(x, y));
	}
	p_list.pop_back();
	file_stream.close();
	return N;
}

void sort_order(std::vector<int>& order){
	int size = order.size();
	if (order[1] < order[size - 2]) return;
	std::vector<int> tmp(order);
	for (int i = 1; i < size - 1; ++i){
		order[i] = tmp[size - i - 1];
	}
}
