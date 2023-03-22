#include <cassert>
#include <cmath>
#include <ctime>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include "structures.hpp"
#include "algorithms.hpp"
#include "utils.hpp"


int main (int argc, char* argv[]){
	bool print = false, time = false;
	int algo = 0;
	std::string file= "../data/N1000_0";
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
	// printf("%d\n", dist);

	return 0;
}
