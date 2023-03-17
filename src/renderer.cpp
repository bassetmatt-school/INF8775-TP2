#include <cassert>
#include <vector>
#include "renderer.hpp"

namespace renderer{
	static SDL_Window*   s_window   = nullptr;
	static SDL_Renderer* s_renderer = nullptr;

	void init(void) {
		int init_res = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
		assert(init_res == 0);
		s_window = SDL_CreateWindow("TP2 Plot",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			window_w, window_h,
			0);
		assert(s_window != NULL);
		s_renderer = SDL_CreateRenderer(s_window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		assert(s_renderer != NULL);
	}

	void displayTSP(std::vector<Point> const point_list, std::vector<int> const order) {
		bool run = true;
		bool drawn = false;
		while (run) {
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT:
					run = false;
				break;

				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						run = false;
					break;
					}
				break;
				}
			}
			if (drawn) continue;

			/* Draw part */
			int n_cities = point_list.size();
			Point city1, city2;
			SDL_SetRenderDrawColor(s_renderer, 255, 255, 255, 255);
			SDL_RenderClear(s_renderer);
			/* Draw first point */
			SDL_SetRenderDrawColor(s_renderer, 255, 0, 0, 255);
			SDL_Rect first_point(
				point_list[order[0]].x/2 - rect_size/2,
				point_list[order[0]].y/2 - rect_size/2,
				rect_size,
				rect_size
			);
			SDL_RenderFillRect(s_renderer, &first_point);
			SDL_SetRenderDrawColor(s_renderer, 0, 0, 0, 255);
			for (int i = 0; i < n_cities; ++i) {
				city1 = point_list[order[i]]/2;
				city2 = point_list[order[i+1]]/2;
				SDL_RenderDrawLine(s_renderer, city1.x, city1.y, city2.x, city2.y);
			}
			SDL_RenderPresent(s_renderer);
		}
	}
}
