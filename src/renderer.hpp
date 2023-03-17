#ifndef TP2_RENDERER_H
#define TP2_RENDERER_H

#include <SDL2/SDL.h>
#include "structures.hpp"

namespace renderer {
	int const window_h = 1000;
	int const window_w = 1000;

	int const rect_size = 6;
	void init(void);
	void displayTSP(
		std::vector<Point> const point_list,
		std::vector<int> const order
	);
}

#endif /* TP2_RENDERER_H */
