#include <cmath>
#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

#define INF numeric_limits<int>::max()

/* README
 *  This week we continue with Graphs and explore path finding algorithms.
 *  We explore Dijkstra's algorithm, Bellman-Ford's algorithm, the A* algorithm
 *  as well as algorihms such as Ford-Fulkerson and Edmonds-Karp that can be
 * applied to Network Flow problems.
 *
 *  I've written the exercise descriptions for you to implement how you choose.
 *
 */

using namespace std;

#include <random>

// Modified
int getRandomNumber(int lower, int upper) {
  // from C++11 - more reliable than the older C-style srand() function:
  random_device rd;   // obtain a random seed from the hardware
  mt19937 eng(rd());  // Standard Mersenne Twister engine seeded with rd()
  uniform_int_distribution<int> distribution(
      lower,
      upper);  // distribution from lower to upper bound that are passed in

  int randomNumber = distribution(eng);  // generate random number

  return randomNumber;
}



class Vertex {
  public:
    vector<pair<Vertex *, int>> neighbours; // Modified to store weights against edges
    string name;
    Vertex(string initName, vector<pair<Vertex *, int>> initNeighbours = {}) {
      neighbours = initNeighbours;
      name = initName;
    }
    void addEdge(Vertex *neighbour, int weight) { // Modified to accept weight parameter
      neighbours.push_back(make_pair(neighbour, weight)); // Store neighbour and weight as a pair
    }
    string displayNeighbours() {
      string s = "";
      for (auto neighbour : neighbours) {
        s += neighbour.first->name;
        s += ", ";
      }
      return s;
    }
};
class Graph {
  public:
    vector<Vertex *> vertices;
    Graph(vector<Vertex *> initVertices = {}) { vertices = initVertices; }
    void addVertex(Vertex *vertex) { vertices.push_back(vertex); }
    void display() {
      for (auto vertex : vertices) {
        cout << "Vertex " << vertex->name << " has neighbours "
             << vertex->displayNeighbours() << endl;
      }
    }
};

/*
 * Exercise 1: Dijkstra's Algorithm
 * Either with the graph provided above (or with your Graph implementation from
 * last week), create a graph with the edges as described below:
 *
 *        B -  D
 *      / | \  | \
 *    A   |  \ |  F
 *      \ |   \| /
 *        C -  E
 *
 * Edge weights are:
 *
 * A->B = 2
 * A->C = 4
 *
 * B->C = 1
 * B->D = 4
 * B->E = 2
 *
 * C->E = 3
 *
 * D->F = 2
 *
 * E->D = 3
 * E->F = 2

 *
 *
 * Implement Dijkstra's algorithm to find the shortest path between node A and F
 * in the above graph. Output the path to screen to confirm. If implemented
 * correctly you should see: A->B->D->F
 *
 * Extension 1: If you haven't already, apply priority queues in Dijkstra's
 * algorithm utilise min-heaps (priority queues). Extension 2: If you had to
 * draw the Graph in a terminal view, how would you format your display method?
 *
 * Question: What would happen if you were to add a connection from C->A with a
 * non-negative weight and re-run Dijkstra's algorithm? Question: What would
 * happen if you were to modify the edge from A->B with the weight -2 and re-run
 * Dijkstra's algorithm?
 *
 */

// Below is a simplified pseudocode of Dijkstra's algorithm to get you started:

/*
    Dijkstra(G, s):
    distances <- list of length equal to the number of nodes of the graph, initially it has all its elements equal to infinite
    distances[s] = 0
    queue = the set of vertices of G
    while queue is not empty:
         u <- vertex in queue with min distances[u]
         remove u from queue
         for each neighbor v of u:
              temp = distances[u] + value(u,v)
              if temp < distances[v]:
                    distances[v] = temp
    return distances
*/

/*
 * Exercise 2: Dijkstra return map of shortest path values
 * Now modify your implementation of Dijkstra's algorithm to return
 * a map of shortest paths to all nodes in graph (not just A to F).
 *
 * For example,
 * The map/dictionary returned would have corresponding shortest path value to
 * each node in the graph:
 *
 * A : 0
 * B : 2
 * C : 3
 * D : 6
 * E : 4
 * F : 6
 *
 */

struct Path {
  int distance;
  optional<string> previous;
};

Vertex *findAndRemoveMinimumElement(list<Vertex *> &elements,
                                    unordered_map<string, Path> vertexPath) {
  list<Vertex *>::iterator minElement;
  Vertex *ret;
  int infinity = numeric_limits<int>::max();
  int minDistance = infinity;
  list<Vertex *>::iterator it;

  // This is where a priority queue (aka min heap) would help,
  // by allowing us to get the minimum value in O(1).
  // Without that, we have to iterate over all elements to find the minimum.
  for (it = elements.begin(); it != elements.end(); it++) {
    const Path path = vertexPath[(*it)->name];
    // It should be the case, even on first iteration,
    // that at least one element (the starting node) has distance less than infinity.
    // However, we don't explicitly initialise `minElement` so if somehow that were
    // not the case, bad stuff would happen.
    if (path.distance < minDistance) {
      minDistance = path.distance;
      minElement = it;
    }
  }
  // If we used a vector (or any array-backed data structure), we would need
  // another pass to remove the minimum element (by copying the rest of the elements).
  // But by using a linked list, we can remove the minimum element in O(1).
  ret = *minElement;
  elements.erase(minElement);

  return ret;
}

unordered_map<string, Path> dijkstra(Graph *g, Vertex *start) {
  unordered_map<string, Path> vertexPath;
  list<Vertex *> unvisitedVertices;
  Vertex * current;
  for (auto &vertex : g->vertices) {
    unvisitedVertices.push_back(vertex);
    if (vertex->name == start->name) {
      vertexPath[vertex->name] = {
        .distance = 0,
        .previous = nullopt
      };
    } else {
      vertexPath[vertex->name] = {
        .distance = numeric_limits<int>::max(),
        .previous = nullopt
      };
    }
  }

  while (!unvisitedVertices.empty()) {
    current = findAndRemoveMinimumElement(unvisitedVertices, vertexPath);
    for (auto &neighbour : current->neighbours) {
      // Update distance (if less)
      const int weightToNeighbour = neighbour.second;
      const int neighbourNewDistance = vertexPath[current->name].distance + weightToNeighbour;
      const int neighbourCurrentDistance = vertexPath[(neighbour.first)->name].distance;
      if (neighbourNewDistance < neighbourCurrentDistance) {
        vertexPath[(neighbour.first)->name].previous = current->name;
        vertexPath[(neighbour.first)->name].distance = neighbourNewDistance;
      };
    }
  }
  return vertexPath;
};

/*
 * Exercise 3: Bellman-Ford Algorithm
 * The Bellman-Ford (Richard Bellman and Lester Ford Jr, 1958) algorithm
 * can be used to compute shortest paths on graphs that include negative edge
 * weights. Start by translating the pseudocode below, adapting this to work
 * with your implementation.
 *
 * Question: How does the performance of this algorithm compare with Dijkstra's
 * algorithm? Question: Could Dijkstra's be modified to work with negative edge
 * weights?
 *
 * Extension: Also check that your Bellman-Ford implementation works on an
 * unweighted graph. e.g. set all the edge weights to 1 for all connections in
 * your graph.
 */

// Here's some pseudocode to get you started:

/*
function BellmanFord(Graph, source):
    // Step 1: Initialization
    distances = array of size |V| initialized with infinity
    distances[source] = 0

    // Step 2: Relax edges repeatedly
    for i from 1 to |V| - 1:
        for each edge (u, v, weight) in Graph:
            if distances[u] + weight < distances[v]:
                distances[v] = distances[u] + weight

    // Step 3: Check for negative cycles
    for each edge (u, v, weight) in Graph:
        if distances[u] + weight < distances[v]:
            return "Graph contains a negative cycle"

    return distances
*/

/*
 * Exercise 4: A* Algorithm algorithm
 * The A* algorithm introduces a heuristic (a strategy/prior knowledge of
 * context) to find a path between two vertices/nodes in an environment. You are
 * welcome to define your own environment to test this algorithm. Here is a
 * simple matrix to get you started:
 *
 *   {S, 0, 0, 0, 0},
 *   {0, 1, 1, 0, 0},
 *   {0, 0, 0, 0, 0},
 *   {1, 0, 0, 1, 1},
 *   {0, 0, 0, 0, E}
 *
 * Above, S represents the starting position, and E the finish position. 0s are
 * navigable spaces, whereas 1s represent obstacles which you cannot pass
 * through.
 *
 * It would be advisable to use a priority queue to explore the nodes with the
 * lowest total cost (sum of the cost from the start node to the current node
 * and the heuristic estimate from the current node to the goal). Start with a
 * Euclidean heuristic (straight line/as the crow flies). Some pseudocode has
 * been provided below for you to modify to your implementation.
 *
 * Extension: Now apply the Manhattan heuristic (Grid approach/equal distances
 * between blocks) to this algorithm. Question: Which of the two heuristics are
 * more effective for this problem? What are your observations here?
 *
 */

// Pseudocode for A*

/*
function AStarWithEuclideanDistance(start, goal):
    // Initialize open and closed lists
    open_list = priority queue initialized with start node
    closed_list = empty set

    // Set g score of start node to 0
    start.g = 0

    while open_list is not empty:
        // Get node with lowest f score from open list
        current = node with lowest f score in open_list

        // Check if current node is the goal
        if current is goal:
            return reconstructPath(current)

        // Move current node from open to closed list
        remove current from open_list
        add current to closed_list

        // Expand current node's neighbors
        for each neighbor of current:
            if neighbor is not traversable or neighbor is in closed_list:
                continue

            // Calculate tentative g score for neighbor
            tentative_g = current.g + distance(current, neighbor)

            if neighbor is not in open_list or tentative_g < neighbor.g:
                // Update neighbor's parent and g score
                neighbor.parent = current
                neighbor.g = tentative_g

                // Calculate Euclidean distance heuristic from neighbor to goal
                neighbor.h = euclideanDistance(neighbor, goal)

                // Add neighbor to open list (or update priority if already in
open list) if neighbor is not in open_list: add neighbor to open_list with
priority f = g + h else: update priority of neighbor in open_list to f = g + h

    // No path found
    return "No path found"

function reconstructPath(node):
    path = empty list
    while node is not null:
        prepend node to path
        node = node.parent
    return path
*/

/*
 * Exercise 5: Network Flow Problems
 *
 * Each edge in the network (graph) has a capacity, which represents the maximum
 * amount of flow that can pass through that edge. The flow along each edge must
 * not exceed its capacity. The total amount of flow entering the node must
 * equal the total amount of flow leaving the node. This principle is known as
 * conservation of flow and ensures that resources are maintained in the
 * network/graph. The goal of Maximum-Flow algorithms is to determine the
 * maximum amount of flow that can be sent from the source to the destination
 * (sink) while respecting the capacity constraints and satisfying the
 * conservation of flow at each node.
 *
 * This has applications in engineering, transport, digital infrastructure etc.
 *
 * The key difference here in this application is that our edge weights will
 * refer to the CAPACITY, rather than the distance. Either reuse a previous
 * graph or create a suitable new graph which has multiple pathways from source
 * to destination (sink).
 *
 * Start by applying the Ford-Fulkerson algorithm (which here utilises BFS) with
 * the pseudocode below. In many cases, large maximum flow values are considered
 * desirable because they indicate that the network can efficiently accommodate
 * a high volume of resource flow from the source to the sink.
 *
 * Extension: Implement the Edmonds-Karp algorithm on the same graph and
 * evaluate the differences in performance. Question:  Which is more effective
 * for maximum-flow: DFS or BFS?
 */

// Here is some pseudocode for the Ford-Fulkerson method:

/*
function FordFulkerson(Graph, source, sink):
    // Initialize flow on all edges to 0
    for each edge in Graph:
        edge.flow = 0

    // Initialize residual graph with capacities equal to original capacities
    residualGraph = copy of Graph

    // Initialize total flow to 0
    totalFlow = 0

    // Repeat until no augmenting path exists from source to sink
    while there exists an augmenting path from source to sink in residualGraph:
        // Find augmenting path using any suitable method (e.g., BFS)
        augmentingPath = findAugmentingPath(residualGraph, source, sink)

        // Find the bottleneck capacity along the augmenting path
        bottleneckCapacity = minCapacityAlongPath(augmentingPath)

        // Augment the flow along the augmenting path
        augmentFlow(residualGraph, augmentingPath, bottleneckCapacity)

        // Update total flow
        totalFlow += bottleneckCapacity

    // Return the maximum flow
    return totalFlow

function findAugmentingPath(residualGraph, source, sink):
    // Use BFS to find a path from source to sink in residualGraph
    // Return the path if found, otherwise return null

function minCapacityAlongPath(path):
    // Find the minimum capacity along the given path
    // Return the minimum capacity

function augmentFlow(residualGraph, path, bottleneckCapacity):
    // Update the flow along the given path in residualGraph by adding
bottleneckCapacity to forward edges
    // and subtracting bottleneckCapacity from backward edges
*/

int main() {
  cout << "C++ DS&A Graphs - Path Finding\n" << endl;
  
  // Ex 1 - Dijkstra's algorithm - shortest path between two nodes
  cout << "Exercise 1: Dijkstra's algorithm" << endl;

  // Create the graph
  Vertex* A = new Vertex("A");
  Vertex* B = new Vertex("B");
  Vertex* C = new Vertex("C");
  Vertex* D = new Vertex("D");
  Vertex* E = new Vertex("E");
  Vertex* F = new Vertex("F");

  A->neighbours.push_back(make_pair(B, 2));
  A->neighbours.push_back(make_pair(C, 4));

  B->neighbours.push_back(make_pair(C, 1));
  B->neighbours.push_back(make_pair(D, 4));
  B->neighbours.push_back(make_pair(E, 2));

  C->neighbours.push_back(make_pair(E, 3));

  D->neighbours.push_back(make_pair(F, 2));

  E->neighbours.push_back(make_pair(D, 3));
  E->neighbours.push_back(make_pair(F, 2));

  Graph *g = new Graph({A, B, C, D, E, F});

  // Ex 2 - Dijkstra's map of shortest paths
  cout << "\nExercise 2: Dijkstra's algorithm - map of shortest paths" << endl;

  auto shortestPaths = dijkstra(g, A);

  // Print shortest paths
  cout << "Shortest Paths:" << endl;
  for (const auto& path : shortestPaths) {
    cout << path.first << ": distance " << path.second.distance << ", previous "
         << path.second.previous.value_or("(no previous)") << endl;
  }
  
  // Ex 3 - Bellman-Ford algorithm for negative weights & unweighted graphs
  cout << "\nExercise 3: Bellman-Ford algorithm - negative weights & "
          "unweighted graphs"
       << endl;

  // Ex 4 - A* Algorithm
  cout << "\nExercise 4: A* Algorithm - heuristics " << endl;

  // Ex 5 - Network Flow
  cout << "\nExercise 5: Maximum Network flow - Ford-Fulkerson vs Edmonds-Karp"
       << endl;

  return 0;
}