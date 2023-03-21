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

#define USE_GREEDY
// #define USE_DP
#define USE_APPROX
#define RENDERING

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

int main (){
	std::vector<Point> p_list;
	int N_cities;
	/* File loading */
	std::string file("../data/DP_N15_0");
	std::cout << "Loading file " << file << std::endl;
	N_cities = load_file(file, p_list);
	std::cout << "File loaded" << std::endl;

	int dist;
	std::vector<int> order;
#ifdef RENDERING
	renderer::init();
#endif /* RENDERING */


	/* Greedy TSP Application */
#ifdef USE_GREEDY
	order = algos::greedy_TSP(p_list);
	// for (int x : order) {printf("%d|", x);}
	// printf("\n");
	dist = 0;
	for (int i = 0; i < N_cities; ++i)
		dist += distance(p_list[order[i]], p_list[order[i+1]]);

	// for (int i = 0; i < order.size() - 1; ++i) {
	// 	int p1 = order[i];
	// 	int p2 = order[i+1];
	// 	int d = distance(p_list[p1], p_list[p2]);
	// 	dist += d;
	// 	printf("Distance %d-%d : %d\n", p1, p2, d);
	// }
	std::cout << "Distance = " << dist << std::endl;

#ifdef RENDERING
	renderer::displayTSP(p_list, order);
#endif /* RENDERING */
#endif /* USE_GREEDY */


	/* Dynamic programming application */
#ifdef USE_DP
	order = algos::dynamic_prog_TSP(p_list);
	dist = order[order.size()-1];
	order.pop_back();
	// for (int x : order) {printf("%d|", x);}
	// printf("\n");
	// 	for (int i = 0; i < order.size() - 1; ++i) {
	// 	int p1 = order[i];
	// 	int p2 = order[i+1];
	// 	int d = distance(p_list[p1], p_list[p2]);
	// 	printf("Distance %d-%d : %d\n", p1, p2, d);
	// }
	std::cout << "Distance = " << dist << std::endl;
#ifdef RENDERING
	renderer::displayTSP(p_list, order);
#endif // RENDERING
#endif // USE_DP

#ifdef USE_APPROX
	algos::approximative_TSP(p_list);
#endif // USE_APPROX
	return 0;
}
