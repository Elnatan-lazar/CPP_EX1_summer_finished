#include "Algorithms.hpp"
#include <iostream>
#include <queue>
#include <vector>
#include <climits>
#include <functional>
#include "Graph.hpp"
#include <limits>
#include <algorithm>

namespace ariel
{
    // Utility function to perform BFS for isConnected
    static void bfs(const Graph &g, int start, std::vector<bool> &visited)
    {
        std::queue<int> q;
        q.push(start);
        visited[static_cast<size_t>(start)] = true;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (size_t v = 0; v < g.getNumVertices(); ++v)
            {
                if (g.getAdjacencyMatrix()[static_cast<size_t>(u)][v] != 0 && !visited[v])
                {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    bool Algorithms::isConnected(const Graph &g)
    {
        size_t vertices = static_cast<size_t>(g.getNumVertices()); // Use size_t for size-related operations
        std::vector<bool> visited(vertices, false);

        bfs(g, 0, visited);

        bool connected = true;
        for (bool v : visited)
        {
            if (!v)
            {
                connected = false;
                break;
            }
        }

        return connected;
    }

    std::string Algorithms::shortestPath(const Graph &g, int start, int end)
    {
        size_t vertices = static_cast<size_t>(g.getNumVertices()); // Use size_t for size-related operations
        std::vector<int> dist(vertices, INT_MAX);
        std::vector<int> pred(vertices, -1);
        std::queue<int> q;

        dist[static_cast<size_t>(start)] = 0;
        q.push(start);

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (size_t v = 0; v < vertices; ++v)
            {
                if (g.getAdjacencyMatrix()[static_cast<size_t>(u)][v] != 0 &&
                    dist[static_cast<size_t>(u)] + g.getAdjacencyMatrix()[static_cast<size_t>(u)][v] < dist[static_cast<size_t>(v)])
                {
                    dist[static_cast<size_t>(v)] = dist[static_cast<size_t>(u)] + g.getAdjacencyMatrix()[static_cast<size_t>(u)][v];
                    pred[static_cast<size_t>(v)] = static_cast<int>(u);
                    q.push(v);
                }
            }
        }

        if (dist[static_cast<size_t>(end)] == INT_MAX)
            return "-1 (no short path)";

        std::string path;
        for (int v = end; v != -1; v = pred[static_cast<size_t>(v)])
        {
            path = std::to_string(v) + "->" + path;
        }
        return path.substr(0, path.length() - 2);
    }

    bool Algorithms::isContainsCycle(const Graph &g)
    {
        size_t vertices = static_cast<size_t>(g.getNumVertices()); // Use size_t for size-related operations
        std::vector<int> parent(vertices, -1);
        std::vector<bool> visited(vertices, false);
        std::vector<int> stack;

        // Define the lambda function for DFS with std::function for recursion
        std::function<bool(int)> dfs = [&](int u) -> bool
        {
            visited[static_cast<size_t>(u)] = true;
            stack.push_back(u);
            for (size_t v = 0; v < vertices; ++v)
            {
                if (g.getAdjacencyMatrix()[static_cast<size_t>(u)][v] != 0)
                {
                    if (!visited[static_cast<size_t>(v)])
                    {
                        parent[static_cast<size_t>(v)] = static_cast<int>(u);
                        if (dfs(v))
                            return true;
                    }
                    else if (v != parent[static_cast<size_t>(u)])
                    {
                        stack.push_back(v);
                        std::string cycle;
                        for (size_t i = stack.size() - 1; i > 0; --i)
                        {
                            cycle += std::to_string(stack[i]) + "->";
                        }
                        cycle += std::to_string(stack[0]);
                        std::cout << "The cycle is: " + cycle << std::endl;
                        return true;
                    }
                }
            }
            stack.pop_back();
            return false;
        };

        for (size_t i = 0; i < vertices; ++i)
        {
            if (!visited[static_cast<size_t>(i)] && dfs(i))
            {
                return true;
            }
        }

        return false;
    }

    std::string Algorithms::isBipartite(const Graph &g)
    {
        size_t vertices = static_cast<size_t>(g.getNumVertices()); // Use size_t for size-related operations
        std::vector<int> color(vertices, -1);

        auto bfs = [&](int start) -> bool
        {
            std::queue<int> q;
            q.push(start);
            color[static_cast<size_t>(start)] = 0;

            while (!q.empty())
            {
                int u = q.front();
                q.pop();
                for (size_t v = 0; v < vertices; ++v)
                {
                    if (g.getAdjacencyMatrix()[static_cast<size_t>(u)][v] != 0)
                    {
                        if (color[static_cast<size_t>(v)] == -1)
                        {
                            color[static_cast<size_t>(v)] = 1 - color[static_cast<size_t>(u)];
                            q.push(v);
                        }
                        else if (color[static_cast<size_t>(v)] == color[static_cast<size_t>(u)])
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        };

        for (size_t i = 0; i < vertices; ++i)
        {
            if (color[static_cast<size_t>(i)] == -1 && !bfs(i))
                return "0 (no bipartite)";
        }

        std::string A, B;

        for (size_t i = 0; i < vertices; ++i)
        {
            if (color[static_cast<size_t>(i)] == 0)
                A += std::to_string(i) + ",";
            else
                B += std::to_string(i) + ",";
        }
        A.pop_back();
        B.pop_back();

        return "The graph is bipartite: A={" + A + "}, B={" + B + "}";
    }

    std::string Algorithms::negativeCycle(const Graph &g)
    {
        size_t V = static_cast<size_t>(g.getNumVertices()); // Use size_t to match the type returned by getNumVertices()
        const auto &adjMatrix = g.getAdjacencyMatrix();

        std::vector<long long> dist(V, std::numeric_limits<long long>::max());
        std::vector<size_t> parent(V, V); // Use size_t for parent indices

        std::vector<size_t> cycle;

        // Initialize distances from source (0) to all other vertices as INFINITE
        dist[0] = 0;

        // Relax edges up to V-1 times
        for (size_t i = 0; i < V - 1; ++i)
        {
            for (size_t u = 0; u < V; ++u)
            {
                for (size_t v = 0; v < V; ++v)
                {
                    if (adjMatrix[u][v] != 0 && dist[u] != std::numeric_limits<long long>::max() &&
                        dist[u] + static_cast<long long>(adjMatrix[u][v]) < dist[v])
                    {
                        dist[v] = dist[u] + adjMatrix[u][v];
                        parent[v] = u; // Use size_t for indices
                    }
                }
            }
        }

        // Check for negative-weight cycles
        for (size_t u = 0; u < V; ++u)
        {
            for (size_t v = 0; v < V; ++v)
            {
                if (adjMatrix[u][v] != 0 && dist[u] != std::numeric_limits<long long>::max() &&
                    dist[u] + static_cast<long long>(adjMatrix[u][v]) < dist[v])
                {
                    // Found negative cycle, reconstruct the cycle path
                    std::vector<bool> inCycle(V, false);
                    size_t x = v; // Use size_t for indices
                    for (size_t i = 0; i < V; ++i)
                    {
                        x = parent[x];
                    }

                    size_t start = x;
                    cycle.push_back(start);
                    x = parent[start];
                    while (x != start)
                    {
                        cycle.push_back(x);
                        x = parent[x];
                    }
                    cycle.push_back(start);
                    std::reverse(cycle.begin(), cycle.end());

                    // Convert cycle to string
                    std::string cycleStr;
                    for (size_t i = 0; i < cycle.size(); ++i)
                    {
                        cycleStr += std::to_string(cycle[i]);
                        if (i < cycle.size() - 1)
                            cycleStr += " -> ";
                    }
                    return "Negative cycle found: " + cycleStr + "\n";
                }
            }
        }

        return "No negative cycle\n";
    }

} // namespace ariel