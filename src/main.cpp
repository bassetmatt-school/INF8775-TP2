#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "renderer.hpp"
#include "point.hpp"


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

int distance(Point const p1, Point const p2) {
	Point v = p1 - p2;
	return std::round(std::sqrt(v.x * v.x + v.y * v.y));
}

std::vector<int> greedyTSP(std::vector<Point> p_list) {
	std::vector<int> result;
	int Ncities = p_list.size();
	std::vector<int> indexes(Ncities);
	std::iota(indexes.begin(), indexes.end(), 0);

	int dist = 0;
	int idx = 0;
	Point city, next_city;
	int mindist, next_idx = 0;
	result.push_back(0);
	for (int i = 0; i < Ncities-1; ++i) {
		mindist = SDL_MAX_SINT32;
		city = p_list[idx];
		p_list.erase( (p_list.begin()  + idx));
		indexes.erase((indexes.begin() + idx));


		int cnt = 0;
		for (Point c :p_list) {
			// std::cout << "  distance: " << distance(c, city) << std::endl;
			if (distance(c, city) <= mindist) {
				next_idx = cnt;
				next_city = c;
				mindist = distance(c, city);
			}
			cnt++;
		}
		idx = next_idx;
		result.push_back(indexes[idx]);
		dist += mindist;
	}
	// result.push_back(0);
	dist += distance(city, p_list[0]);
	result.push_back(0);
	result.push_back(dist);
	return result;
}

int main (){
	std::vector<Point> p_list;
	/* File loading */
	std::string file("../data/N100000_0");
	std::cout << "Loading file " << file << std::endl;
	load_file(file, p_list);
	std::cout << "File loaded" << std::endl;

	/* Greedy TSP Application */
	std::vector<int> order;
	order = greedyTSP(p_list);
	int dist = order[order.size()-1];
	order.pop_back();
	std::cout << "Distance = " << dist << std::endl;

	renderer::init();
	renderer::displayTSP(p_list, order);
	return 0;
}
