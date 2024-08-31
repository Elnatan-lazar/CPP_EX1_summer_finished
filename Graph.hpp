#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>

namespace ariel
{
    extern const std::string RED;
    extern const std::string RESET;
    class Graph
    {

    private:
        std::vector<std::vector<int>> adjacency_matrix;
        int num_vertices;
        int num_edges;
        bool isDirect;
        bool isSubmatrix(const Graph &other) const;
        bool checkIfMatrixEquel(const Graph &other) const;

    public:
        Graph();
        void loadGraph(const std::vector<std::vector<int>> &matrix);
        void printGraph() const;
        void checkIfDirect();
        bool getDirect() const;
        int getNumEdges() const;
        int getNumVertices() const;
        std::vector<std::vector<int>> getAdjacencyMatrix() const;
        Graph operator*(int scalar) const;
        Graph &operator*=(int scalar);
        Graph operator/(int scalar) const;
        Graph &operator/=(int scalar);

        Graph operator*(const Graph &other) const;

        Graph operator+(const Graph &other) const;
        Graph &operator+=(const Graph &other);
        Graph operator-(const Graph &other) const;
        Graph &operator-=(const Graph &other);

        Graph operator+() const; // Unary plus
        Graph operator-() const; // Unary minus

        // Overloaded increment/decrement operators
        Graph &operator++();   // Pre-increment
        Graph operator++(int); // Post-increment
        Graph &operator--();   // Pre-decrement
        Graph operator--(int); // Post-decrement

        friend std::ostream &operator<<(std::ostream &os, const Graph &graph);

        bool operator>(const Graph &other) const;
        bool operator>=(const Graph &other) const;
        bool operator<(const Graph &other) const;
        bool operator<=(const Graph &other) const;
        bool operator==(const Graph &other) const;
        bool operator!=(const Graph &other) const;
    };
}

#endif // GRAPH_HPP