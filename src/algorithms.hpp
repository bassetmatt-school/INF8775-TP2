#ifndef TP2_ALGORITHMS_H
#define TP2_ALGORITHMS_H

#include <vector>
#include "structures.hpp"

namespace algos {
    std::vector<int> greedyTSP(std::vector<Point> p_list);
    std::vector<int> dynamicProgTSP(std::vector<Point> p_list);
}

#endif /* TP2_ALGORITHMS_H */
