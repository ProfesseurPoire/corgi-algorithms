#pragma once

#include <corgi/algorithms/graphs/graph.h>

#include <map>
#include <vector>

namespace graphs
{
struct dijkstra_node
{
    int cost;
    int parent;
};

/**
 * @brief Computes the distance of every node usingfrom the graph relative to @p
 * start using dijkstra's algorithm
 *
 * The goal of this function isn't to have a generic dikstra algorithm that I
 * could use everywhere. It's to have dijkstra implemented in a very simple and
 * easy to understand way, so it can be reused, tweaked or improved later on.
 */

std::map<int, dijkstra_node>
dijkstra(std::map<int, dijkstra_node>  unvisited_nodes,
         std::vector<std::vector<int>> adjancency_matrix,
         int                           start);

void dijkstra_step();

/**
 * @brief
 */
std::vector<int>
dijstra_path(std::map<int, dijkstra_node> gr, int start, int dest);
}    // namespace graphs