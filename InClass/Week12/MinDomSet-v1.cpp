#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <math.h>
#include <string>

static constexpr size_t MAX_NODES = 200;
using nodeset_t = std::bitset<MAX_NODES>;

class Graph {
private:
    size_t num_nodes;
    size_t num_edges;

    struct Node {
        nodeset_t edges;
    };

    std::vector<Node> nodes;

    // Helpful constants
    nodeset_t all_nodes;

public:
    Graph() {
        std::cin >> num_nodes >> num_edges;

        nodes.resize(num_nodes);

        size_t from, to;
        for (size_t i = 0; i < num_edges; ++i) {
            std::cin >> from >> to;
            nodes[from].edges.set(to);
            nodes[to].edges.set(from);
        }

        for (size_t i = 0; i < num_nodes; i++) {
            all_nodes.set(i);
        }
    }

    void PrintFile() {
        std::cout << num_nodes << " " << num_edges << "\n";
        for (size_t node1 = 0; node1 < num_nodes; node1++) {
            for (size_t node2 = node1+1; node2 < num_nodes; node2++) {
                if (nodes[node1].edges.test(node2)) {
                    std::cout << node1 << " " << node2 << "\n";
                }
            }
        }
    }

    size_t SolveMDS(nodeset_t included, nodeset_t undecided) {
        // If nothing is undecided - check if solved!
        nodeset_t powered = included;
        if (undecided.none()) {
            for (size_t i = 0; i < num_nodes; i++) {
                // If this node is included, power it neighbors!
                if (included.test(i)) {
                    powered |= nodes[i].edges;
                }
            }

            // If all nodes are powered, we have a legal solution!
            if (powered == all_nodes) {
                return included.count();  // Return num included.
            }

            // Otherwise, not a legal solution.
            return num_nodes+1;
        }

        // If we still have undecided nodes, choose node to exclude and include.
        size_t next_node = 0;
        while (!undecided.test(next_node)) ++next_node;

        // Remove next node from undecided.
        undecided.reset(next_node);

        size_t result1 = SolveMDS(included, undecided);  // Exclude!

        included.set(next_node);
        size_t result2 = SolveMDS(included, undecided);  // Include!

        return std::min(result1, result2);
    }

    size_t SolveMDS() {
        return SolveMDS(nodeset_t(), all_nodes);
    }
};

int main()
{
    Graph graph;
    size_t result = graph.SolveMDS();

    std::cout << result << std::endl;
}