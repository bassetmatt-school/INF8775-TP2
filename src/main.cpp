#include <cassert>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include "structures.hpp"
#include "algorithms.hpp"


enum Algos{
	GREEDY,
	DP,
	APPROX,
};

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

int main (int argc, char* argv[]){
	bool print = false, time = false;
	int algo = 0;
	std::string file;
	switch (argc) {
		case 1: file = "../data/N1000_0"; break;
		case 5:
			file  = argv[1];
			algo  = *argv[2] - 48;
			print = *argv[3] - 48;
			time  = *argv[4] - 48;
		break;
		default: exit(1); break;
	}
	// printf("File : %s\nAlgo : %d\nPrint: %d\nTime: %d\n", file.c_str(), algo, print, time);

	std::vector<Point> city_list;
	int N_cities = load_file(file, city_list);
	assert(N_cities > 0);

	/* Shared variables for algorithms */
	int dist = 0;
	std::vector<int> order;
	clock_t t1=0, t2=0;
	double time_diff;

	switch (algo) {
		/* Greedy TSP Application */
		case GREEDY:
			t1 = clock();
			order = algos::greedy_TSP(city_list);
			t2 = clock();
			for (int i = 0; i < N_cities; ++i)
				dist += distance(city_list[order[i]], city_list[order[i+1]]);
		break;
		/* Dynamic programming application */
		case DP:
			t1 = clock();
			order = algos::dynamic_prog_TSP(city_list);
			t2 = clock();
			dist = order[order.size()-1];
			order.pop_back();
		break;
		/* Approximate algorithm application */
		case APPROX:
			t1 = clock();
			order = algos::approximative_TSP(city_list);
			t2 = clock();
			for (int i = 0; i < N_cities; ++i)
				dist += distance(city_list[order[i]], city_list[order[i+1]]);
		default:
		break;
	}

	time_diff = ((double) t2 - t1) / CLOCKS_PER_SEC;
	if (time) printf("%f\n", time_diff * 1000);
	if (print) {
		sort_order(order);
		for (int x: order) {printf("%d\n", x);}
	}
	// printf("Distance = %d\n", dist);

	return 0;
}
