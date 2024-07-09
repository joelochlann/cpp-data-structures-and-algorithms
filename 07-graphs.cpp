#include <iostream>
#include <list>
#include <map>  // for dictionary like behaviour
#include <queue>
#include <stack>
#include <utility>  // For std::pair
#include <vector>
#include <unordered_set>

/* README
 *  In this week, we'll look at Graphs: directed and undirected, weighted and
 * unweighted. We'll also apply the BFS and DFS algorithms and make adaptions.
 *  We'll set up classes to represent these using indexed structures and
 * referenced structures.
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

/*
 * Exercise 1: Implement a Graph class with a indexed structure
 * Create a Graph class and model the adjacent vertices as a matrix (e.g. a 2D
 * array). This matrix should hold the weights (the edges) for the connections
 * between vertices. In main, instantiate a Graph object, add vertices, and
 * connect these together with edges.
 *
 * Write a print/display method and check that you can visualise the adjacency
 * matrix. Below is a sample output to give you an example of the vertices (A-E)
 * and their edge connections:
 *
 *   A B C D E
 * A 0 1 0 0 7
 * B 0 4 0 7 0
 * C 2 0 5 0 0
 * D 0 0 0 9 0
 * E 0 4 0 8 0
 *
 */
class MatrixGraph {
  public:
    vector<vector<int>> matrix;
    MatrixGraph() {}

    int addVertex() {
      // Add row
      vector<int> newRow = {};
      // TODO: some nice "fill" function could be better?
      // create row of old size. if 0... zero length
      for (size_t i = 0; i < matrix.size(); i++) {
        newRow.push_back(0);
      }
      // now we have 1 row, 0 cols
      matrix.push_back(newRow);

      // Add column
      for (auto& row : matrix) {
        row.push_back(0);
      }
      return matrix.size() - 1;
    }

    void addEdge(int start, int end) {
      matrix[start][end]++;
    }

    void display() {
      for (auto row : matrix) {
        for (auto col : row) {
          cout << col << " ";
        }
        cout << endl;
      }
    }
};

/*
 * Exercise 2: Implement a Graph with a referenced structure
 * Now implement a Graph that uses an adjacency list, rather than a matrix.
 * You could model the connections from each vertex as individual lists.
 * You could build the edge weights into the nodes of each list, as these would
 * individual to each connection. You could use your LinkedList class from
 * previous exercises or select an appropriate STL structure - a pair, list, map
 * or other.
 *
 * Set up a new Graph, with vertices and edges and check these are stored
 * correctly in the adjacency list. Create a print / display method to check.
 *
 */
class Vertex {
  public:
    vector<Vertex *> neighbours;
    string name;
    Vertex(string initName, vector<Vertex *> initNeighbours = {}) {
      neighbours = initNeighbours;
      name = initName;
    }
    void addEdge(Vertex *neighbour) {
      neighbours.push_back(neighbour);
    }
    string displayNeighbours() {
      string s = "";
      for (auto neighbour : neighbours) {
        s += neighbour->name;
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
 * Exercise 3: DFS using a Stack
 *
 * Either refactor the DFS function you used for your 06 Tree exercise sheet,
 * or write a DFS function that will search the depth of the connections
 * from a starting node/vertex in the graph.
 *
 * Extension 1: If you already have a working DFS using your user-defined Stack
 * class from previous weeks, why not refactor this to use the STL's stack?
 * Extension 2: Can you use DFS to detect whether there is a cycle in the graph?
 */
optional<string> dfs(Vertex *root, string nameToFind) {
  stack<Vertex *> vertexStack;
  unordered_set<string> visited;
  vertexStack.push(root);
  while (!vertexStack.empty()) {
    Vertex *current = vertexStack.top();
    vertexStack.pop();
    cout << "Visiting " << current->name << endl;
    visited.insert(current->name);
    if (current->name == nameToFind) {
      return current->name;
    }
    // Go from right to left! Because it will be popped in reverse order
    vector<Vertex *> neighbours = current->neighbours;
    for (int i = neighbours.size() - 1; i >= 0; i--) {
      if (!visited.contains(neighbours[i]->name)) {
        vertexStack.push(neighbours[i]);
      }
    }
  }
  return nullopt;
}

/*
 * Exercise 4: BFS using a Queue
 *
 * Either refactor the BFS function you used for your 06 Tree exercise sheet,
 * or write a BFS function that will search the breadth of the connections
 * from a starting node/vertex in the graph.
 *
 * Note: In 08 Path Finding, we will use BFS in Dijkstra's algorithm for
 * unweighted graphs. Therefore, it's helpful to check this functions works
 * ahead of then.
 *
 */
optional<string> bfs(Vertex *root, string stringToFind) {
  queue<Vertex *> vertexQueue;
  unordered_set<string> visited;
  vertexQueue.push(root);
  while (!vertexQueue.empty()) {
    Vertex *current = vertexQueue.front();
    vertexQueue.pop();
    visited.insert(current->name);
    cout << "Visiting " << current->name << endl;
    if (current->name == stringToFind) {
      return current->name;
    }
    for (Vertex *neighbour : current->neighbours) {
      if (!visited.contains(neighbour->name)) {
        vertexQueue.push(neighbour);
      }
    }
  }
  return nullopt;
}

/*
 * Exercise 5: Topological Sort
 * Topological Sort orders vertices so that each node/vertex appears only after
 * all the nodes pointing to it have appeared. Apply your DFS algorithm, in
 * combination with a structure to print nodes of graph by these rules. This
 * could be done via a vector or a hash table / unordered_map.
 *
 * Example: For a graph with 4 nodes and these relations: a->b, a->c, b->d,
 * c->d, there are two acceptable topological sorts: a, b, c, d and a, c, b, d.
 *
 * Note: Topological Sort is not feasible in graphs that have a cycle.
 *       Therefore, it is helpful to first detect whether a graph has a cycle.
 *       If you've already completed the extension for exercise 3 (DFS), feel
 * free to reuse this here.
 *
 */

int main() {
  cout << "C++ DS&A Graphs\n" << endl;

  // Ex 1 - Set up a Graph and connect vertices together with a matrix and add
  // edges
  cout << "Exercise 1: Complete the Graph class with a indexed structure"
       << endl;
  MatrixGraph *mg = new MatrixGraph();
  int a = mg->addVertex();
  int b = mg->addVertex();
  int c = mg->addVertex();
  int d = mg->addVertex();
  int e = mg->addVertex();
  mg->addEdge(a, b);
  mg->addEdge(b, a);
  mg->addEdge(c, e);
  mg->addEdge(c, e);
  mg->display();

  // Ex 2 - Set up a Graph and connect vertcies (nodes) together with a
  // referenced structure
  cout << "Exercise 2: Complete the Graph class with a referenced structure"
       << endl;
  Vertex *va = new Vertex("a");
  Vertex *vb = new Vertex("b");
  Vertex *vc = new Vertex("c");
  Vertex *vd = new Vertex("d");
  Vertex *ve = new Vertex("e");
  va->addEdge(vb);
  vb->addEdge(va);
  vc->addEdge(ve);
  vc->addEdge(ve);
  // Unlike a tree, there is no clear starting node (root)
  // and if we pick the wrong one there may be no path to 
  // any other nodes so there would be no way of traversing.
  Graph *g = new Graph({va, vb, vc, vd, ve});
  g->display();

  // Ex 3 - DFS.
  cout << "\nExercise 3: Depth-First Search of a Graph" << endl;
  optional<string> maybeB = dfs(va, "b");
  cout << "Result of searching: " << maybeB.value_or("not found!") << endl;

  optional<string> maybeE = dfs(va, "e");
  cout << "Result of searching: " << maybeE.value_or("not found!") << endl;

  vb->addEdge(vc);
  maybeE = dfs(va, "e");
  cout << "Result of searching: " << maybeE.value_or("not found!") << endl;

  // Ex 4 - BFS
  cout << "\nExercise 4: Breadth-First Search of a Graph " << endl;
  maybeB = bfs(va, "b");
  cout << "Result of searching: " << maybeB.value_or("not found!") << endl;

  maybeE = bfs(va, "e");
  cout << "Result of searching: " << maybeE.value_or("not found!") << endl;

  optional<string> maybeD = bfs(va, "d");
  cout << "Result of searching: " << maybeD.value_or("not found!") << endl;

  // Ex 5 - Topological Sort
  cout << "\nExercise 5: Topological Sort" << endl;

  return 0;
}