#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "structures.hpp"
#include "renderer.hpp"
#include "algorithms.hpp"

void load_file(std::string const& filename, std::vector<Point>& p_list){
	std::ifstream file_stream(filename);
	if (!file_stream.is_open()) {
		std::cout << "Couldn't open file\n";
		return;
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
}

int main (){
	std::vector<Point> p_list;
	/* File loading */
	std::string file("../data/N10000_0");
	std::cout << "Loading file " << file << std::endl;
	load_file(file, p_list);
	std::cout << "File loaded" << std::endl;

	/* Greedy TSP Application */
	std::vector<int> order;
	order = algos::greedyTSP(p_list);
	int dist = order[order.size()-1];
	order.pop_back();
	std::cout << "Distance = " << dist << std::endl;

	renderer::init();
	renderer::displayTSP(p_list, order);
	return 0;
}
