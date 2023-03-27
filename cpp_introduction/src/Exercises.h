#pragma once

#include <algorithm>
#include <map>
#include <numeric>
#include <set>
#include <span>
#include <tuple>
#include <vector>
#include <queue>

struct Tree;

////////////////// Exercise 1 ////////////////////////////////////
std::pair<float, float> Statistics(std::span<const float> values) {
    float total = 0;
    for (float num: values) {
        total += num;
    }
    float average = total / values.size();

    float variance = 0;
    for (float num: values) {
        variance += pow(num - average, 2);
    }

    float stddev = sqrt(variance / values.size());
    return {average, stddev};
}
//////////////////////////////////////////////////////////////////

////////////////// Exercise 2 ////////////////////////////////////
class TreeVisitor {
public:
    float visitTreeHelper(const Tree &tree, bool countOnlyEvenLevels, int currentLevel) {
        float sum = 0;
        if (currentLevel % 2 == 0 || !countOnlyEvenLevels) {
            sum += tree.value;
        }

        for (const auto &child: tree.children) {
            sum += visitTreeHelper(child, countOnlyEvenLevels, currentLevel + 1);
        }
        return sum;
    }

    float visitTree(const Tree &tree, bool countOnlyEvenLevels) {
        return visitTreeHelper(tree, countOnlyEvenLevels, 0);
    }
};
//////////////////////////////////////////////////////////////////

////////////////// Exercise 3 ////////////////////////////////////
class Complex {
public:
    Complex(float real_, float imaginary_) {
        real = real_;
        im = imaginary_;
    }

    Complex operator+(const Complex &other) const {
        Complex result(real + other.real, im + other.im);
        return result;
    }

    Complex operator-(const Complex &other) const {
        Complex result(real - other.real, im - other.im);
        return result;
    }

    Complex operator*(const Complex &other) const {
        float a = real;
        float b = im;
        float c = other.real;
        float d = other.im;
        Complex result(a * c - b * d, a * d + b * c);
        return result;
    }

    Complex operator/(const Complex &other) const {
        Complex result(real / other.real, im / other.im);
        return result;
    }

    float real, im;
};
//////////////////////////////////////////////////////////////////

////////////////// Exercise 4 ////////////////////////////////////
float WaterLevels(std::span<const float> heights) {
    int n = heights.size();
    if (n < 3) return 0;

    // Find the peak of the surface
    int peak = 0;
    for (int i = 1; i < n; i++) {
        if (heights[i] > heights[peak]) {
            peak = i;
        }
    }

    // Traverse the surface from left to right
    float water = 0;
    float left_max = heights[0];
    for (int i = 1; i < peak; i++) {
        if (heights[i] > left_max) {
            left_max = heights[i];
        } else {
            water += left_max - heights[i];
        }
    }

    // Traverse the surface from right to left
    float right_max = heights[n - 1];
    for (int i = n - 2; i > peak; i--) {
        if (heights[i] > right_max) {
            right_max = heights[i];
        } else {
            water += right_max - heights[i];
        }
    }

    return water;
}
//////////////////////////////////////////////////////////////////

////////////////// Exercise 5 ////////////////////////////////////
using location = std::pair<int, int>;

int Labyrinth(const std::set<std::pair<location, location>> &labyrinth, int size) {
    std::vector<std::vector<bool>> visited(size, std::vector<bool>(size, false));
    std::vector<std::vector<int>> distance(size, std::vector<int>(size, 0));

    // BFS starting from (0,0)
    std::queue<location> q;
    q.emplace(0, 0);
    visited[0][0] = true;

    while (!q.empty()) {
        location curr = q.front();
        q.pop();

        // Check if we reached the target
        if (curr.first == size - 1 && curr.second == size - 1) {
            return distance[curr.first][curr.second] + 1;
        }

        // Generate neighbors
        std::vector<location> neighbors;
        if (curr.first > 0) {
            neighbors.emplace_back(curr.first - 1, curr.second);
        }
        if (curr.first < size - 1) {
            neighbors.emplace_back(curr.first + 1, curr.second);
        }
        if (curr.second > 0) {
            neighbors.emplace_back(curr.first, curr.second - 1);
        }
        if (curr.second < size - 1) {
            neighbors.emplace_back(curr.first, curr.second + 1);
        }

        // Add unvisited neighbors to the queue
        for (const auto &neighbor: neighbors) {
            if (!visited[neighbor.first][neighbor.second] &&
                labyrinth.count({curr, neighbor}) == 0 &&
                labyrinth.count({neighbor, curr}) == 0) {
                q.push(neighbor);
                visited[neighbor.first][neighbor.second] = true;
                distance[neighbor.first][neighbor.second] =
                        distance[curr.first][curr.second] + 1;
            }
        }
    }

    // No path found
    return 0;
}
//////////////////////////////////////////////////////////////////
