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

    // Track the best.
    nodeset_t best_result;
    size_t best_size;

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

        best_size = num_nodes+1;
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

    void PrintBest() {
        for (size_t i = 0; i < num_nodes; i++) {
            if (best_result.test(i)) {
                std::cout << " " << i;
            }
        }
        std::cout << std::endl;
    }

    size_t SolveMDS(nodeset_t included, nodeset_t undecided) {
        const size_t cur_size = included.count();

        // If nothing is undecided - check if solved!
        nodeset_t powered = included;
        if (undecided.none() || cur_size + 1 >= best_size) {
            for (size_t i = 0; i < num_nodes; i++) {
                // If this node is included, power it neighbors!
                if (included.test(i)) {
                    powered |= nodes[i].edges;
                }
            }

            // If all nodes are powered, we have a legal solution!
            if (powered == all_nodes) {
                if (cur_size < best_size) {
                    best_size = cur_size;
                    best_result = included;
                }

                return cur_size;  // Return num included.
            }

            // Otherwise, not a legal solution.
            return num_nodes+1;
        }

        // If any vertices are exclude, as are all their neighbors, STOP!
        nodeset_t active_nodes = included | undecided;
        nodeset_t excluded = ~active_nodes & all_nodes;

        // for (size_t i = 0; i < num_nodes; i++) {
        //     // If this node is exclude and NONE of it neighbors are active,
        //     // then backtrack!
        //     if (excluded.test(i) &&
        //         (nodes[i].edges & active_nodes).none()) {
        //         return num_nodes + 1;
        //     }
        // }


        for (size_t i = 0; i < num_nodes; i++) {
            // If this node is exclude and NONE of it neighbors are active,
            // then backtrack!
            if (excluded.test(i)) {
                size_t active_neighbor_count =
                    (nodes[i].edges & active_nodes).count();
                if (active_neighbor_count == 0) {
                    return num_nodes + 1;
                }
                if (active_neighbor_count == 1) {
                    // FIND ACTIVE NEIGHBOR AND INCLUDE THEM!
                }
            }
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

    std::cout << result << std::endl << "Best:";
    graph.PrintBest();
}