#pragma once

#include <vector>

namespace graph
{

/**
 * @brief An edge connects 2 cells. Cells are identified by their index in the
 * cell list
 */
struct edge
{
    int first;
    int second;
};

struct graph
{
    std::vector<int>              cells;
    std::vector<edge>             edges;
    std::vector<std::vector<int>> adjacency_matrix;

    /**
     * @brief Creates the adjacency matrix from the defined cells and edges
     */
    void build_adjacency_matrix()
    {
        adjacency_matrix.resize(cells.size());

        for(auto& line : adjacency_matrix)
            line.resize(cells.size(), 0);

        for(auto& [first, second] : edges)
        {
            adjacency_matrix[first][second] = 1;
            adjacency_matrix[second][first] = 1;
        }
    }
};

struct dikstra_cell
{
    int cost;
};

/**
 * @brief Object that is returned by the dijkstra function. It returns the cost
 * of every node compared to the first one given to the function
 */
struct dijkstra_result
{
    std::vector<dikstra_cell> cells;
};

/**
 * Functions that implements the dijkstra algorithm. By defaults, dijkstra
 * doesn't find the path. It updates the cost of every node compared to the
 * start node.
 *
 * The goal here is just to get a working example. I'd probably wants edges to
 * be weighted or other informations.
 */
std::vector<dijkstra_result> dikstra(graph gr, int start, int dest);
}    // namespace graph