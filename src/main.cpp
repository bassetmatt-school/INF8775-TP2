#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <SDL2/SDL.h>

#define WINDOW_W 1000
#define WINDOW_H 800

SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;

class Point {
public:
	int x,y;
	Point() {this->x = 0; this->y = 0;}
	Point(int x, int y) { this->x = x; this->y = y;}
	Point copy() {return Point(this->x, this->y);}
	Point operator+(const Point& p2) {return Point(this->x + p2.x, this->y + p2.y);}
	Point operator-(const Point& p2) {return Point(this->x - p2.x, this->y - p2.y);}
	Point operator-() {return Point(-this->x, -this->y);}
	Point operator*(const float& k) {return Point(k * this->x, k * this->y);}
	Point& operator+=(const Point& p2) {this->x += p2.x; this->y += p2.y; return *this;}
	void pr() {printf("(%d, %d)\n", this->x, this->y);}
};

Point operator*(const int& k, const Point& p2) {return Point(k * p2.x, k * p2.y);}
Point operator-(Point const& p1, Point const& p2){return Point(p1.x - p2.x, p1.y - p2.y);}
using Vec2 = Point;

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
	Vec2 v = p1 - p2;
	return std::floor(std::sqrt(v.x * v.x + v.y * v.y));
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
		// printf("-------------\ni = %d\n", i);
		mindist = SDL_MAX_SINT32;
		city = p_list[idx];
		p_list.erase( (p_list.begin() + idx));
		indexes.erase((indexes.begin() + idx));
		/* Debug */
		// city.pr(); 
		// std::cout << std::endl;
		// for (Point c:p_list) {c.pr();}
		/* Debug */
		
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
	result.push_back(dist);
	return result;
}

int main (int argc, char* argv[]){

	std::string file("../data/N10000_0");
	if (argc == 1) {
		std::cout << argv[1] << std::endl;
	}
	std::vector<Point> p_list;
	load_file(file, p_list);
	// for (Point p : p_list) {p.pr();}
	// std::cout << "Number of points : " << p_list.size() << std::endl;
	std::vector<int> order;
	order = greedyTSP(p_list);
	int dist = order[order.size()-1];
	order.pop_back();
	// std::cout << "Order : ";
	// for (int i : order) {printf("%d - ", i);}
	// std::cout << 0 << std::endl;
	std::cout << "Distance = " << dist << std::endl;
	
	
	// g_window = SDL_CreateWindow("TP2", 
	// 	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	// 	WINDOW_W, WINDOW_H,
	// 	0);
	// g_renderer = SDL_CreateRenderer(g_window, -1,
	// 	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	// SDL_Event event;
	// bool run = true;
	// while (run) {
	// 	while (SDL_PollEvent(&event)) {
	// 		if (event.type == SDL_QUIT || 
	// 		   (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
	// 			run = false;
	// 	}
	// 	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	// 	SDL_RenderClear(g_renderer);
	// 	SDL_RenderPresent(g_renderer);
	// }
	return 0;
}