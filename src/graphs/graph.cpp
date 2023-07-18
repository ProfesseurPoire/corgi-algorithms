#include <corgi/algorithms/graphs/graph.h>

#include <algorithm>
#include <map>
#include <ranges>

namespace graphs
{

void graph::build_adjacency_matrix()
{
    adjacency_matrix.resize(nodes);

    for(auto& line : adjacency_matrix)
        line.resize(nodes, 0);

    for(auto& [first, second, cost] : edges)
    {
        adjacency_matrix[first][second] = cost;
        adjacency_matrix[second][first] = cost;
    }
}

}    // namespace graphs