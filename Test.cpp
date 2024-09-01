// elnatan100@gmail.com
#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace ariel;

TEST_CASE("Test isConnected")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("Test shortestPath")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1 (no short path)");
}
TEST_CASE("Test isContainsCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isContainsCycle(g) == false);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == true);
}
TEST_CASE("Test isBipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0,2}, B={1}");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "0 (no bipartite)");

    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 0},
        {1, 0, 3, 0, 0},
        {0, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0,2,4}, B={1,3}");
}
TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));
}

TEST_CASE("Test operator* (scalar multiplication) 1")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);

    Graph result = g * 2;

    vector<vector<int>> expected = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};
    CHECK(result.getAdjacencyMatrix() == expected);
}

TEST_CASE("Test operator*= (scalar multiplication) 2")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);

    g *= 3;

    vector<vector<int>> expected = {
        {0, 3, 0},
        {3, 0, 3},
        {0, 3, 0}};
    CHECK(g.getAdjacencyMatrix() == expected);
}

TEST_CASE("Test operator/= (scalar division) 4")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 6, 0},
        {6, 0, 6},
        {0, 6, 0}};

    g.loadGraph(graph);

    g /= 2;

    vector<vector<int>> expected = {
        {0, 3, 0},
        {3, 0, 3},
        {0, 3, 0}};
    CHECK(g.getAdjacencyMatrix() == expected);
}

TEST_CASE("Test operator+ (Unary plus) 10")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);

    Graph result = +g;

    CHECK(result.getAdjacencyMatrix() == g.getAdjacencyMatrix());
}

TEST_CASE("Test operator- (Unary minus) 11")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);

    Graph result = -g;

    vector<vector<int>> expected = {
        {0, -1, 0},
        {-1, 0, -1},
        {0, -1, 0}};
    CHECK(result.getAdjacencyMatrix() == expected);
}

TEST_CASE("Test pre-increment and post-increment operators 12")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);

    ++g;

    vector<vector<int>> expectedPre = {
        {1, 2, 1},
        {2, 1, 2},
        {1, 2, 1}};
    CHECK(g.getAdjacencyMatrix() == expectedPre);

    g++;

    vector<vector<int>> expectedPost = {
        {2, 3, 2},
        {3, 2, 3},
        {2, 3, 2}};
    CHECK(g.getAdjacencyMatrix() == expectedPost);
}

TEST_CASE("Test comparison operators 14")
{
    Graph g1, g2, g3;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 0, 0}};
    vector<vector<int>> graph2 = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};
    vector<vector<int>> graph3 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 0, 0}};

    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    g3.loadGraph(graph3);

    // CHECK(g1 < g2);

    CHECK((g2 > g1) == true);
    CHECK((g1 == g3) == true);
    CHECK((g1 != g2) == true);
    CHECK((g1 <= g3) == true);
    CHECK((g2 >= g1) == true);
}
TEST_CASE("Test negetive cycle")
{
    std::vector<std::vector<int>> graph10 = {
        {0, 1, 0, 3},  // A
        {0, 0, -1, 0}, // B
        {0, 0, 0, -1}, // C
        {0, -1, 0, 0}  // D
    };
    // ariel::Graph g5;
    ariel::Graph g5;
    g5.loadGraph(graph10);

    CHECK((ariel::Algorithms::negativeCycle(g5)) == "Negative cycle found: 1 -> 2 -> 3 -> 1\n");
}
TEST_CASE("Test empty matrix throws exception")
{
    std::vector<std::vector<int>> emptyGraph; // Create an empty vector
    ariel::Graph g;

    CHECK_THROWS_AS(g.loadGraph(emptyGraph), std::invalid_argument);
}

TEST_CASE("Test empty matrix throws exception")
{
    std::vector<std::vector<int>> graph = {
        {1, 1, 0, 3},  // A
        {0, 1, -1, 0}, // B
        {0, 0, 1, -1}, // C
        {0, -1, 0, 1}  // D
    }; // the diagnel not 0
    ariel::Graph g;

    CHECK_THROWS_AS(g.loadGraph(graph), std::invalid_argument);
}
