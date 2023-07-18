#pragma once

#include <map>
#include <vector>

namespace graphs
{

/**
 * @brief An edge connects 2 nodes. Nodes are identified by their index in the
 * cell list
 */
struct edge
{
    int first;
    int second;

    // Cost between first and second nodes;
    int cost = 1;
};

struct graph
{
    int                           nodes;
    std::vector<edge>             edges;
    std::vector<std::vector<int>> adjacency_matrix;

    /**
     * @brief Creates the adjacency matrix from the defined nodes and edges
     */
    void build_adjacency_matrix();
};

}    // namespace graphs