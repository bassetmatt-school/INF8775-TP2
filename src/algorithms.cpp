#include <climits>
#include <iostream>
#include <numeric>
#include "algorithms.hpp"
namespace algos {
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
            mindist = INT32_MAX;
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

    std::vector<int> dynamicProgTSP(std::vector<Point> p_list) {

        return std::vector<int>(0);
    }
}
