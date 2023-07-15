#pragma once

#include <map>
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
    int                           nodes;
    std::vector<edge>             edges;
    std::vector<std::vector<int>> adjacency_matrix;

    /**
     * @brief Creates the adjacency matrix from the defined cells and edges
     */
    void build_adjacency_matrix()
    {
        adjacency_matrix.resize(nodes);

        for(auto& line : adjacency_matrix)
            line.resize(nodes, 0);

        for(auto& [first, second] : edges)
        {
            adjacency_matrix[first][second] = 1;
            adjacency_matrix[second][first] = 1;
        }
    }
};

struct dijkstra_node
{
    int index;
    int cost;
    int parent;
};

/**
 * Functions that implements the dijkstra algorithm. By defaults, dijkstra
 * doesn't find the path. It updates the cost of every node compared to the
 * start node.
 *
 * The goal here is just to get a working example. I'd probably wants edges to
 * be weighted or other informations.
 */
std::map<int, dijkstra_node> dijkstra(graph gr, int start, int dest);

std::vector<int>
dijstra_path(std::map<int, dijkstra_node> gr, int start, int dest);

}    // namespace graph