#include <climits>
#include <cassert>
#include <iostream>
#include <numeric>
#include "algorithms.hpp"
namespace algos {
    PathTable* g_dist_table = nullptr;
    PathTable* g_path_table = nullptr;

    std::vector<int> greedy_TSP(std::vector<Point> p_list) {
        std::vector<int> result;
        int N_cities = p_list.size();
        std::vector<int> indexes(N_cities);
        std::iota(indexes.begin(), indexes.end(), 0);

        int idx = 0;
        Point city, next_city;
        int min_dist, next_idx = 0;
        result.push_back(0);
        for (int i = 0; i < N_cities-1; ++i) {
            min_dist = INT32_MAX;
            city = p_list[idx];
            p_list.erase( (p_list.begin()  + idx));
            indexes.erase((indexes.begin() + idx));

            int cnt = 0;
            for (Point c :p_list) {
                // std::cout << "  distance: " << distance(c, city) << std::endl;
                if (distance(c, city) <= min_dist) {
                    next_idx = cnt;
                    next_city = c;
                    min_dist = distance(c, city);
                }
                cnt++;
            }
            idx = next_idx;
            result.push_back(indexes[idx]);
        }
        result.push_back(0);
        return result;
    }

    void backtrack_path(Path full_path, std::vector<int>& order) {
        int n_cities = order.size();
        Path p = full_path;
        uint8_t point = get_point(p);
        Set s = get_set(p);
        order[0] = point;
        for (int i = 1; i < n_cities; ++i) {
            point = g_path_table->at(p);
            s = (s == 0) ? s : remove(s, point);
            p = constr(point, s);
            order[i] = point;
        }
    }

    int dyn_prog_rec(Path p, std::vector<Point> const& p_list) {
        Set s = get_set(p);
        uint8_t i = get_point(p);
        if (s == 0) {
            return g_dist_table->at(path_from_point(i));
        } else if (contains(s, i)) {
            return INT32_MAX;
        }
        int min_pt = -1;
        int min_dist = INT32_MAX;
        /* Iterates on s elements */
        for (uint8_t j = 0; j < 32; ++j) {
            if (!contains(s, j)) continue;
            int dij = distance(p_list[i], p_list[j]);

            Set s_ = remove(s, j);
            Path key = constr(j, s_);
            if (!g_dist_table->contains(key)) {
                int dist = dyn_prog_rec(key, p_list);
                g_dist_table->insert(TableIndex(key, dist));
            }
            int dist = dij + g_dist_table->at(key);
            if (dist < min_dist) {
                min_pt = j;
                min_dist = dist;
            }
        }
        Path key = constr(i, s);
        g_dist_table->insert(TableIndex(key, min_dist));
        g_path_table->insert(TableIndex(key, min_pt));
        return min_dist;
    }

    std::vector<int> dynamic_prog_TSP(std::vector<Point> p_list) {
        g_dist_table = new PathTable();
        g_path_table = new PathTable();

        assert(g_dist_table != nullptr);
        assert(g_path_table != nullptr);

        int n_cities = p_list.size();
        Point const arrival = p_list[0];

        /* First line of the table */
        for (int i = 1; i < n_cities; ++i) {
            Path i_to_zero = path_from_point(i);
            int dist_to_zero = distance(p_list[i], arrival);
            g_dist_table->insert(TableIndex(i_to_zero, dist_to_zero));
        }
        Path full_path = constr(0, initSet(n_cities));
        int tot_dist = dyn_prog_rec(full_path, p_list);

        std::vector<int> order(n_cities);
        backtrack_path(full_path, order);

        // tot_dist += distance(p_list[order[order.size()-1]], arrival);
        order.push_back(0);
        order.push_back(tot_dist);
        return order;
    }

    void prim_algo(std::vector<Point> p_list) {
        auto h = p_list[0];
        h.pr();
    }

    std::vector<int> approximative_TSP(std::vector<Point> p_list) {
        auto h = p_list[0];
        h.pr();
        return std::vector<int>(0);
    }
}
