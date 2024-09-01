// elnatan100@gmail.com
#include "Graph.hpp"
#include <iostream>
#include <iomanip>
namespace ariel
{
    const std::string RED = "\033[31m";  // Red text
    const std::string RESET = "\033[0m"; // Reset to default color
    Graph::Graph() : num_vertices(0), num_edges(0), isDirect(false), adjacency_matrix() {}
    // ANSI escape codes for colors

    void Graph::loadGraph(const std::vector<std::vector<int>> &matrix)
    {
        if (matrix.empty())
        {
            throw std::invalid_argument("Error: The input matrix is empty.");
        }
        // Check if the matrix is square
        size_t n = matrix.size();
        int r = 0;
        for (const auto &row : matrix)
        {
            r++;
            if (row.size() != n)
            {
                throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
            }
        }

        if (r != n)
        {
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
        }

        // Load the matrix
        adjacency_matrix.clear();
        adjacency_matrix = matrix;
        num_vertices = n;
        num_edges = 0;
        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = 0; j < n; ++j)
            {

                if (adjacency_matrix[i][j] != 0 && i == j)
                {

                    throw std::invalid_argument("Invalid graph: need to be 0 in the main diagnal, matrix == 0");
                }
            }
        }
        checkIfDirect(); // check if the Graph derict

        // Count the edges
        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = 0; j < n; ++j)
            {
                if (adjacency_matrix[i][j] != 0)
                {
                    num_edges++;
                }
            }
        }
        // if (!isDirect)
        // {
        //     num_edges = num_edges / 2; // if it undirect graph we nee to dived the edges by 2 to prevent duplicate.
        // }
    }

    void Graph::checkIfDirect()
    {
        size_t n = adjacency_matrix.size();
        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = 0; j < n; ++j)
            {

                if (adjacency_matrix[i][j] != adjacency_matrix[j][i])
                {
                    isDirect = true;
                }
            }
        }
    }

    int Graph::getNumEdges() const
    {

        return num_edges;
    }

    void Graph::printGraph() const
    {
        std::cout << "Graph with " << num_vertices << " vertices and " << getNumEdges() << " edges." << std::endl;
    }
    int Graph::getNumVertices() const
    {
        return num_vertices;
    }
    bool Graph::getDirect() const
    {
        return isDirect;
    }

    std::vector<std::vector<int>> Graph::getAdjacencyMatrix() const
    {
        return adjacency_matrix;
    }

    ariel::Graph ariel::Graph::operator*(int scalar) const
    {
        Graph result;

        // Copy the number of vertices and edges
        result.num_vertices = num_vertices;
        result.num_edges = num_edges;
        result.isDirect = isDirect;

        result.loadGraph(this->adjacency_matrix);

        // Multiply each element by the scalar
        for (size_t i = 0; i < num_vertices; ++i)
        {
            for (size_t j = 0; j < num_vertices; ++j)
            {
                result.adjacency_matrix[i][j] = adjacency_matrix[i][j] * scalar;
            }
        }

        // Recalculate the number of edges if needed
        result.num_edges = 0;
        for (size_t i = 0; i < num_vertices; ++i)
        {
            for (size_t j = 0; j < num_vertices; ++j)
            {
                if (result.adjacency_matrix[i][j] != 0)
                {
                    result.num_edges++;
                }
            }
        }
        if (scalar == 0)
        {
            result.isDirect = true;
        }

        if (!result.isDirect)
        {
            result.num_edges = result.num_edges / 2; // Adjust for undirected graphs
        }

        return result;
    }

    Graph Graph::operator+(const Graph &other) const
    {
        if (num_vertices != other.num_vertices)
        {
            throw std::invalid_argument("Graphs must be of the same size for addition.");
        }

        Graph result = *this; // Copy current graph to result

        for (size_t i = 0; i < num_vertices; ++i)
        {
            for (size_t j = 0; j < num_vertices; ++j)
            {
                result.adjacency_matrix[i][j] += other.adjacency_matrix[i][j];
            }
        }
        result.checkIfDirect(); // chek if now its dircet graph;

        return result;
    }

    // Overload += operator
    Graph &ariel::Graph::operator+=(const Graph &other)
    {
        if (num_vertices != other.num_vertices)
        {
            throw std::invalid_argument("Graphs must be of the same size for addition.");
        }

        for (size_t i = 0; i < num_vertices; ++i)
        {
            for (size_t j = 0; j < num_vertices; ++j)
            {
                adjacency_matrix[i][j] += other.adjacency_matrix[i][j];
            }
        }
        this->checkIfDirect(); // chek if now its dircet graph;

        return *this;
    }

    // Overload unary + operator
    Graph Graph::operator+() const
    {
        return *this; // Unary + returns a copy of the current graph
    }

    // Overload - operator
    Graph Graph::operator-(const Graph &other) const
    {
        if (num_vertices != other.num_vertices)
        {
            throw std::invalid_argument("Graphs must be of the same size for subtraction.");
        }

        Graph result = *this; // Copy current graph to result

        for (size_t i = 0; i < num_vertices; ++i)
        {
            for (size_t j = 0; j < num_vertices; ++j)
            {
                result.adjacency_matrix[i][j] -= other.adjacency_matrix[i][j];
            }
        }
        result.checkIfDirect(); // chek if now its dircet graph;

        return result;
    }

    // Overload -= operator
    ariel::Graph &ariel::Graph::operator-=(const Graph &other)
    {
        if (num_vertices != other.num_vertices)
        {
            throw std::invalid_argument("Graphs must be of the same size for subtraction.");
        }

        for (size_t i = 0; i < num_vertices; ++i)
        {
            for (size_t j = 0; j < num_vertices; ++j)
            {
                adjacency_matrix[i][j] -= other.adjacency_matrix[i][j];
            }
        }
        this->checkIfDirect(); // //chek if now its dircet graph;

        return *this;
    }

    // Overload unary - operator
    Graph Graph::operator-() const
    {
        Graph result = *this; // Copy current graph to result

        for (size_t i = 0; i < num_vertices; ++i)
        {
            for (size_t j = 0; j < num_vertices; ++j)
            {
                result.adjacency_matrix[i][j] = -adjacency_matrix[i][j];
            }
        }

        return result;
    }

    // Pre-increment
    Graph &Graph::operator++()
    {

        for (size_t i = 0; i < num_vertices; ++i)
        {
            for (size_t j = 0; j < num_vertices; ++j)
            {
                adjacency_matrix[i][j] += 1;
            }
        }

        return *this;
    }

    // Post-increment
    Graph ariel::Graph::operator++(int)
    {
        Graph temp = *this; // Save the current state
        ++(*this);          // Use pre-increment to update the current object
        return temp;        // Return the old state
    }

    // Pre-decrement
    ariel::Graph &ariel::Graph::operator--()
    {
        for (size_t i = 0; i < num_vertices; ++i)
        {
            for (size_t j = 0; j < num_vertices; ++j)
            {
                adjacency_matrix[i][j] -= 1;
            }
        }

        return *this;
    }

    // Post-decrement
    ariel::Graph ariel::Graph::operator--(int)
    {
        Graph temp = *this; // Save the current state
        --(*this);          // Use pre-decrement to update the current object
        return temp;        // Return the old state
    }

    std::ostream &operator<<(std::ostream &os, const Graph &graph)
    {
        os << "Graph with " << graph.num_vertices << " vertices and " << graph.getNumEdges() << " edges." << std::endl;

        if (graph.adjacency_matrix.empty())
            return os;

        size_t rows = graph.adjacency_matrix.size();
        size_t cols = graph.adjacency_matrix[0].size();

        // Print column indices
        os << "  ";
        for (size_t col = 0; col < cols; ++col)
        {
            os << RED << std::setw(3) << (col + 1) << RESET; // Print column index in red
        }
        os << std::endl;

        // Print rows with row indices and matrix values
        for (size_t row = 0; row < rows; ++row)
        {
            os << RED << std::setw(2) << (row + 1) << RESET; // Print row index in red
            for (size_t col = 0; col < cols; ++col)
            {
                os << std::setw(3) << graph.adjacency_matrix[row][col]; // Print matrix value
            }
            os << std::endl;
        }

        return os;
    }

    Graph &Graph::operator*=(int scalar)
    {

        for (auto &row : adjacency_matrix)
        {
            for (auto &value : row)
            {
                value *= scalar;
            }
        }

        return *this;
    }

    Graph Graph::operator/(int scalar) const
    {
        if (scalar == 0)
        {
            throw std::invalid_argument("Cannot divide by zero.");
        }

        Graph result = *this;
        return result *= (1 / static_cast<double>(scalar)); // Multiply by reciprocal
    }

    Graph &Graph::operator/=(int scalar)
    {
        if (scalar == 0)
        {
            throw std::invalid_argument("Cannot divide by zero.");
        }
        for (auto &row : adjacency_matrix)
        {
            for (auto &value : row)
            {
                value /= scalar;
            }
        }
        return *this;
    }

    bool Graph::isSubmatrix(const Graph &other) const
    {
        // if the other graph has more vertices or edges it cant be a sub graph of the this graph
        if (other.num_vertices > this->num_vertices || other.num_edges > this->num_edges)
        {

            return false;
        }

        int count = 0;

        // for a graph in this class to be an sub graph it need to have the same vertices and the same edges
        //  for exemple if in g1 has an edge 1 -> 2 in wight 3 also g2 need tp have the same edge withe the same wight or bigger from 1 -> 2
        for (size_t i = 0; i < other.num_vertices; ++i)
        {
            for (size_t j = 0; j < other.num_vertices; ++j)
            {
                if (adjacency_matrix[i][j] >= other.adjacency_matrix[i][j])
                {
                    count++;
                }
            }
        }
        if (count == other.num_edges)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Graph::operator>(const Graph &other) const
    {

        if (other.isSubmatrix(*this) || checkIfMatrixEquel(other)) // if this graph is sub graph of other graph or they are equels so this not > the other
        {
            return false;
        }
        if (this->isSubmatrix(other))
        {
            return true;
        }
        if (this->num_edges > other.num_edges)
        {
            return true;
        }
        else if (this->num_edges < other.num_edges)
        {
            return false;
        }

        if (this->num_vertices > other.num_vertices)
        {
            return true;
        }
        else if (this->num_vertices < other.num_vertices)
        {
            return false;
        }
        return false;
    }

    bool Graph::operator>=(const Graph &other) const
    {
        return (*this > other) || (*this == other);
    }

    bool Graph::operator<(const Graph &other) const
    {

        if (checkIfMatrixEquel(other)) // if this graph is sub graph of other graph or they are equels so this not > the other
        {
            return false;
        }
        if (other.isSubmatrix(*this))
        {
            return true;
        }
        if (this->num_edges < other.num_edges)
        {
            return true;
        }
        else if (this->num_edges > other.num_edges)
        {
            return false;
        }

        if (this->num_vertices > other.num_vertices)
        {
            return false;
        }
        else if (this->num_vertices < other.num_vertices)
        {
            return true;
        }
        return false;
    }

    bool Graph::operator<=(const Graph &other) const
    {
        return !(*this > other);
    }

    bool Graph::checkIfMatrixEquel(const Graph &other) const
    {
        if (other.num_vertices != this->num_vertices)
        {
            return false;
        }

        for (size_t i = 0; i < other.num_vertices; ++i)
        {

            for (size_t j = 0; j < other.num_vertices; ++j)
            {
                if (adjacency_matrix[i][j] != other.adjacency_matrix[i][j])
                {
                    return false;
                }
            }
        }

        return true;
    }

    bool Graph::operator==(const Graph &other) const
    {

        if (checkIfMatrixEquel(other) == true)
        { // check if the matrixes equel
            return true;
        }
        if (*this > other || *this < other)
        {
            return false;
        }
        return true;
    }

    bool Graph::operator!=(const Graph &other) const
    {
        return !(*this == other);
    }

    Graph Graph::operator*(const Graph &other) const
    {
        if (adjacency_matrix[0].size() != other.adjacency_matrix.size())
        {
            throw std::invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
        }

        size_t m = adjacency_matrix.size();          // Number of rows in this matrix
        size_t n = other.adjacency_matrix[0].size(); // Number of columns in other matrix
        size_t k = adjacency_matrix[0].size();       // Number of columns in this matrix and rows in other matrix

        std::vector<std::vector<int>> result(m, std::vector<int>(n, 0));

        // Perform matrix multiplication

        for (size_t i = 0; i < m; ++i)
        {
            for (size_t j = 0; j < n; ++j)
            {
                for (size_t l = 0; l < k; ++l)
                {
                    result[i][j] += adjacency_matrix[i][l] * other.adjacency_matrix[l][j];
                }
            }
        }

        // Set diagonal elements to zero
        for (size_t i = 0; i < m; ++i)
        {
            if (i < n) // Ensure diagonal index is within bounds
            {
                result[i][i] = 0;
            }
        }

        // Create a new Graph object with the result
        Graph result_graph;
        result_graph.loadGraph(result);
        return result_graph;
    }
}