#include <corgi/algorithms/graph.h>

#include <algorithm>
#include <map>
#include <ranges>

namespace graph
{

std::vector<int>
dijstra_path(std::map<int, dijkstra_node> nodes, int start, int dest)
{
    std::vector<int> path;

    auto n = nodes[dest];

    while(n.parent != -1)
    {
        path.insert(path.begin(), n.index);
        n = nodes[n.parent];
    }

    path.insert(path.begin(), start);

    return path;
}

std::map<int, dijkstra_node> dijkstra(graph gr, int start, int dest)
{
    dest = 5;

    // List of nodes to inspects
    std::map<int, dijkstra_node> inspected_nodes;

    // List of nodes that haven't been visited yet
    // We use a map because we want to identify the nodes by their id.
    std::map<int, dijkstra_node> unvisited_nodes;

    // I simply copy the nodes of the given graph
    for(int i = 0; i < gr.nodes; i++)
        unvisited_nodes.emplace(i, dijkstra_node {i, 999999999});

    // This will be used to return the best path between start and dest
    std::vector<int> shortest_path_list;

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
        inspected_nodes.emplace(minimal_node_key, minimal_node);
        unvisited_nodes.erase(minimal_node_key);

        // This part uses the adjacency matrix to figure out
        // the neighbors of the node we picked
        int r = -1;
        for(const auto j : gr.adjacency_matrix[minimal_node_key])
        {
            r++;

            // If j is equal to zero it means there's no neighbor
            if(j == 0)
                continue;

            // If we already visited the node we skip it
            if(inspected_nodes.contains(r))
                continue;

            if((minimal_node.cost + 1) < unvisited_nodes.at(r).cost)
            {
                unvisited_nodes.at(r).cost   = minimal_node.cost + 1;
                unvisited_nodes.at(r).parent = minimal_node.index;
            }
        }
    }

    return inspected_nodes;
}

}    // namespace graph