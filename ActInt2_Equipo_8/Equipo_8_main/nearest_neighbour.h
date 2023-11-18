#pragma once

#include <vector>
#include <limits.h>
#include <math.h>

using namespace std;

pair<int, int> nearest_neighbour(vector<pair<int, int>> &points, pair<int, int> &targuet){
    // brute force
    float min_dist = INT_MAX;
    pair<int, int> min_pair;

    for (auto point : points){
        float dist = sqrt(pow(point.first - targuet.first, 2) + pow(point.second - targuet.second, 2));
        if (dist < min_dist){
            min_dist = dist;
            min_pair = point;
        }
    }

    return min_pair;    
}