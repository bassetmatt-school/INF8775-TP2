#ifndef TP2_ALGORITHMS_H
#define TP2_ALGORITHMS_H

#include <vector>
#include "structures.hpp"

namespace algos {
    std::vector<int> greedy_TSP(std::vector<Point> p_list);
    std::vector<int> dynamic_prog_TSP(std::vector<Point> p_list);
}

#endif /* TP2_ALGORITHMS_H */
