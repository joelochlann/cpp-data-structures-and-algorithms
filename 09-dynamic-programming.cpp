#include <limits.h>

#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <utility>
#include <vector>
// #include
// "opt/homebrew/Cellar/boost/1.85.0/include/boost/graph/adjacency_list.hpp"
// #include <boost/1.85.0/include/boost/graph/graph_utility.hpp>
// #include <boost/graph/dijkstra_shortest_paths.hpp>
// #include <boost/graph/floyd_warshall_shortest.hpp>

// ND:   /opt/homebrew/Cellar/boost/1.85.0/include/boost/fusion/include/

// g++ -std=c++11 -I /path/to/boost_1_76_0/ simple_boost_graph.cpp -o
// simple_boost_graph g++ -std=c++11 -I /path/to/boost_1_76_0/
// floyd_warshall.cpp -o floyd_warshall

// to compile:
// clang++ -std=c++11 -I /opt/homebrew/Cellar/boost/1.85.0/include  "09 C++ LIVE
// DEMO.cpp" -o 09_dp_LD

// to run:
// ./09_dp_LD

/* README
 *  In this week, we'll explore some dynamic programming techniques.
 *  We'll set up classes to represent these using arrays, vectors and linked
 * lists.
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
 * Exercise 1: Fibonacci numbers
 * Let's warm up by writing a recursive fibonacci function.
 * Remember to add a base case so you can exit the recursive method calls.
 * Now add memoization, which caches fibonacci numbers as they are calculated.
 *
 * Extension: Create an alternative fib function which is iterative and stores
 * computations in a table (bottom-up approach) Question: What are performance
 * differences between iterative/tabulatation approach and the
 * recursive/memoization approach?
 *
 */
int fib(int n) {
  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  return fib(n - 1) + fib(n - 2);
}

unordered_map<int, int> cache;
int fibMemo(int n) {
  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  auto cachedValue = cache.find(n);
  if (cachedValue == cache.end()) {
    // It's not in the cache
    cache[n] = fib(n - 1) + fib(n - 2);
  }
  return cache[n];
}

/*
 * Exercise 2: Longest Common Subsequence (LCS)
 *
 * Given two sequences, find the length of the longest subsequence present in
 * both of them.
 *
 * Step 1. Define a 2D dynamic programming table
 * Step 2. Initialise the base cases.
 * Step 3. Fill the table using the recurrence relation:
 *               If the characters of both sequences match:
 *                   dp[i][j] = dp[i-1][j-1] + 1
 *               else
 *                   dp[i][j] = max(dp[i-1][j], dp[i][j-1])
 * Step 4. The length of the LCS is in dp[m][n] where m and n are the lengths of
 * the two sequences.
 *
 */

/*
 * Exercise 3: Rucksack (knapsack) problem
 * Given a maximum weight that a rucksack (knapsack) can hold, write a function
 * which will determine the most valuable subset of items that can be included
 * in the rucksack without exceeding its weight limit.
 *
 * Inputs will be:
 *   W (the max weight the rucksack can hold)
 *   n (number of items)
 *   The weights and values of the items
 *
 * To go about this problem, start by defining a table where rows represent
 * items and columns represent possible weight capacities.
 */

/*
 * Exercise 4: Floyd Warshall algorithm - all-pairs shortest paths
 * This is a dynamic programming approach to build up the solution for the
 * shortest paths step by step. It considers each pair of vertices and
 * iteratively improves the path between them by considering each possible
 * intermediate vertex.
 *
 * Step 1. Initialization:
 *   Create a 2D array dist where dist[i][j] represents the shortest distance
 * from vertex i to vertex j. Initialize dist[i][j] to the weight of the edge
 * from i to j if it exists, otherwise to infinity. Set dist[i][i] = 0 for all
 * vertices i.
 *
 * Step 2. Dynamic Programming:
 *   Update the distance array dist by considering each vertex as an
 * intermediate vertex and updating the shortest paths accordingly. For each
 * pair of vertices (i, j), update dist[i][j].
 *
 * Step 3. Result:
 *   After considering all vertices as intermediate vertices, the dist array
 * contains the shortest paths between all pairs of vertices.
 *
 *
 */

/*
 * Exercise 5: Graph Boost
 * Start by checking you have access to the C++ Boost library
 * Create a graph with Boost's adjacency_list function
 * Then apply Boost's Dijkstra's algorithm to work out the shortest path to all
 * vertices. Also apply Boost's Floyd Warshall's all-pairs shortest path
 * algorithm.
 *
 * Question: what are the differences between your implementation
 *   and Boost's implementation of the Floyd Warshall's algorithm?
 *
 */

int main() {
  cout << "C++ DS&A Dynamic Programming\n" << endl;

  // Ex 1 - Fibonnaci - from recursion to vector cache
  cout << "Exercise 1: Fibonnaci numbers with Recursion/Memoization" << endl;
  cout << "fib(0): " << fib(0) << endl;
  cout << "fib(1): " << fib(1) << endl;
  cout << "fib(2): " << fib(2) << endl;
  cout << "fib(3): " << fib(3) << endl;
  cout << "fib(10): " << fib(10) << endl;
  cout << "fib(40): " << fib(40) << endl;
  cout << "fibMemo(40): " << fibMemo(40) << endl;

  // Ex 2 - LCS
  cout << "\nExercise 2: Longest Common Subsequence (LCS)" << endl;

  string X = "AGGTAB";
  string Y = "GXTXAYB";

  // Ex 3 - Knapsack (Rucksack) Problem
  cout << "\nExercise 3: Knapsack (Rucksack) Problem" << endl;

  // Ex 4 - Floyd-Warshall algorithm - all-pairs shortest paths
  cout << "\nExercise 4: Floyd Warshall algorithm - all-pairs shortest paths"
       << endl;

  // Ex 5 - Graphs with Boost
  cout << "\nExercise 5: Graph using Boost's Adjacency List and Dijkstra's "
          "algorithm"
       << endl;

  return 0;
}