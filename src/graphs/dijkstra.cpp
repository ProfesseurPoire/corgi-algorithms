#include <corgi/algorithms/graphs/dijkstra.h>

#include <algorithm>
#include <limits>

namespace graphs
{

std::vector<int>
dijstra_path(std::map<int, dijkstra_node> nodes, int start, int dest)
{
    std::vector<int> path;

    auto n     = nodes[dest];
    auto index = dest;

    while(n.parent != -1)
    {
        path.insert(path.begin(), index);
        index = n.parent;
        n     = nodes[n.parent];
    }

    path.insert(path.begin(), start);

    return path;
}

std::map<int, dijkstra_node>
dijkstra(std::map<int, dijkstra_node>  unvisited_nodes,
         std::vector<std::vector<int>> adjacency_matrix,
         int                           start)
{
    // List of nodes that have already been inspected
    std::map<int, dijkstra_node> visited_nodes;

    // We mark the start node with a cost of 0. The others are set to infinity
    unvisited_nodes[start].cost   = 0;
    unvisited_nodes[start].parent = -1;

    // As long as we haven't visited the whole graph
    while(!unvisited_nodes.empty())
    {
        // I get the node of minimal cost
        auto [minimal_node_key, minimal_node] =
            *std::min_element(unvisited_nodes.begin(), unvisited_nodes.end(),
                              [](const auto& a, const auto& b)
                              { return a.second.cost < b.second.cost; });

        // We add that node to the list of visited nodes
        visited_nodes.emplace(minimal_node_key, minimal_node);
        unvisited_nodes.erase(minimal_node_key);

        // We use an adjacency matrix to figure out the neighbors of the node we
        // picked
        for(std::size_t i = 0; i < adjacency_matrix[minimal_node_key].size();
            i++)
        {
            auto cost = adjacency_matrix[minimal_node_key][i];

            // If j equals zero it means there's no neighbor
            if(cost == 0)
                continue;

            // If we already visited the node we skip it
            if(visited_nodes.contains((int)i))
                continue;

            // Now we check if the cost is less that previously computed.
            // If so, we replace the value and update the parent.
            // The parent is only there to make it easy to find the path
            if((minimal_node.cost + cost < unvisited_nodes.at((int)i).cost))
            {
                unvisited_nodes.at((int)i).cost   = minimal_node.cost + cost;
                unvisited_nodes.at((int)i).parent = minimal_node_key;
            }
        }
    }

    return visited_nodes;
}
}    // namespace graphs
