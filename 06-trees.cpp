#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>

/* README
 *  In this week, we'll look at Trees, Binary Search Trees (BSTs), and also AVL
 * trees (self-balancing) We'll set up classes to represent these using arrays
 * and linked nodes. I'll let you code the classes this week, so you don't have
 * to move the class definitions around!
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
 * Exercise 1: Arranging Nodes in a Tree structure
 * Let's start by creating a Tree class, which enables users to add Nodes/Links
 * in layers. You could add Node objects which represent either string data or
 * integer data. For now, there is no limit to how many 'children' each layer
 * can have. The user would have to indicate which layer the node sits in.
 *
 * Create traversal methods for 'in-order', 'pre-order' and 'post-order'. Test
 * these work and observe the differences in output.
 *
 * Extension: Represent a file directory of folders and the files they contain,
 * as a tree. Question:  Which traversal method would maintain the structure of
 * the file directory?
 *
 * Feel free to make up the directory (or use your file directory), but here's
 * an example : /usr /nick /Documents /Teaching Materials /Research /GitHub /C++
 * DSA /Python /Java
 *
 */

class TreeNode {
 private:
  vector<TreeNode *> children;
  string contents;

 public:
  TreeNode(string contents, vector<TreeNode *> children) {
    this->contents = contents;
    this->children = children;
  }
  vector<TreeNode *> getChildren() { return children; }
  string getContents() { return contents; }
  void traversePreOrder() {
    cout << contents << endl;
    for (TreeNode *n : getChildren()) {
      n->traversePreOrder();
    }
  }

  // TODO: this doesn't work properly yet
  void traverseInOrder() {
    // No single definition of what this means for a general (non-binary) tree!
    // I'll go with: output first child, then parent, then remaining children
    int i = 0;
    for (TreeNode *n : getChildren()) {
      if (i == 0) {
        // first child
        n->traverseInOrder();
      }
      cout << contents << endl;
      if (i > 0) {
        n->traverseInOrder();
      }
      i++;
    }
  };
};

// class Node {
//     private:
//         vector<Node *> children;
//         string contents;
//         Node *getLeftmostDescendant() {
//             if (getChildren().size() == 0) {
//                 return this;
//             }
//             getChildren()[0]->getLeftmostDescendant();
//         }

//     public:
//         Node(string contents, vector<Node *> children) {
//             this->contents = contents;
//             this->children = children;
//         }
//         vector<Node *> getChildren() {
//             return children;
//         }
//         void addChild(Node *child) {
//             children.push_back(child);
//         }
//         void traversePreOrder() {
//             // Print node contents
//             cout << contents << endl;
//             for (Node *n : getChildren()) {
//                 n->traversePreOrder();
//             }
//         }
// };

/*
 * Exercise 2: Binary Search Tree class
 * Now create a BST class which will enforce these rules of insertion:
 * Maximum of two children per layer.
 * The left child's value must be less than the root.
 * The right child's value must be greater than the root.
 *
 * First add test data (integers or strings) and print out the BST to confirm
 * the items are arranged in correct order, according to the rules. Then run
 * your Binary Search algorithm (W2) to check that you can efficiently search
 * and return a value in logarithmic time.
 *
 * If you've implemented this with integer values, now sort strings by
 * alphabetical order. Or vice versa if you started with strings, sort integers
 * in order.
 *
 * Extension 1: Now code a delete function, which should manage pointers when a
 * node is deleted from the BST. Extension 2: If you're using pointers to
 * connect the Nodes together, modify the BST to use an array?
 *
 */
class BSTNode {
  public:
    int value;
    BSTNode *left;
    BSTNode *right;

    BSTNode(int value) {
      this->value = value;
    }

    void insert(int valueToInsert) {
      if (valueToInsert == value) {
        // Value is already in tree
        return;
      }
      if (valueToInsert < value) {
        if (left) {
          left->insert(valueToInsert);
        } else {
          left = new BSTNode(valueToInsert);
        }
      } else {
        // it's greater
        if (right) {
          right->insert(valueToInsert);
        } else {
          right = new BSTNode(valueToInsert);
        }
      }
    }

    void traverseInOrder() {
      if (left) {
        left->traverseInOrder();
      }
      cout << value << endl;
      if (right) {
        right->traverseInOrder();
      }
    }
};

/*
 * Exercise 3: DFS
 * Implement a Depth-First Search function, utilising either your Stack class
 * from last week, or the STL's stack. Test this works on a tree with digits.
 *
 * Extension: If you implemented the extension on the file directory, check that
 * you can locate a file (represented as a 'string') via DFS and print the full
 * path of this file (with preceeding folders).
 *
 */
optional<TreeNode *> dfs(TreeNode *tree, string stringToFind) {
  stack<TreeNode *> s;
  s.push(tree);
  while (!s.empty()) {
    TreeNode *current = s.top();
    s.pop();
    cout << "Visiting " << current->getContents() << endl;
    if (current->getContents() == stringToFind) {
      return current;
    }
    // Go from right to left! Because it will be popped in reverse order
    vector<TreeNode *> children = current->getChildren();
    for (int i = children.size() - 1; i >= 0; i--) {
      s.push(children[i]);
    }
  }
  return nullopt;
}

optional<TreeNode *> dfsRecursive(TreeNode *node, string stringToFind) {
  cout << "Visiting " << node->getContents() << endl;
  if (node->getContents() == stringToFind) {
    return node;
  }
  for (TreeNode *child : node->getChildren()) {
    auto result = dfsRecursive(child, stringToFind);
    if (result) {
      return result;
    }
  }
  return nullopt;
}

/*
  * Exercise 4: BFS
  * Implement a Breadth-First Search function, utilising either your Queue
  * class from last week, or the STL's queue. Test this works on a tree with
  * digits.
  *
  *
  */
optional<TreeNode *> bfs(TreeNode *tree, string stringToFind) {
  queue<TreeNode *> q;
  q.push(tree);
  while (!q.empty()) {
    TreeNode *current = q.front();
    q.pop();
    cout << "Visiting " << current->getContents() << endl;
    if (current->getContents() == stringToFind) {
      return current;
    }
    for (TreeNode *child : current->getChildren()) {
      q.push(child);
    }
  }
  return nullopt;
}

/*
 * Exercise 5: AVL Tree
 * Challenge! Can you now extend your BST to balance itself when new nodes are
 * added (or deleted). The idea is to maintain the rules of a BST (left < root,
 * right > root) but to strive for symmetry where new inserts (or deletions)
 * make the tree too 'one-sided'. This was popularised by George Adelson-Velsky
 * and Evgenii Landis - known as an AVL tree.
 *
 * To break this problem down into manageable steps, focus on testing left
 * rotations and right rotations. I'm happy for you to use either digits or
 * letters as values sorted and arranged.
 *
 * If you can get this working for insertions, check that the tree also
 * re-balances itself for when you delete a given node from a tree.
 */

int main() {
  cout << "C++ DS&A Trees\n" << endl;

  // Ex 1 - Set up the Tree class
  cout << "Exercise 1: Setting up a Tree" << endl;
  // Create a tree of strings and check the three types of traversal
  TreeNode *tree = new TreeNode("years", {
    new TreeNode("2018", {
      new TreeNode("Jan", {
        new TreeNode("1", {}),
        new TreeNode("2", {})
      })
    }),
    new TreeNode("2019", {}),
    new TreeNode("2020", {}),
  });
  tree->traversePreOrder();

  cout << "=======" << endl;
  cout << "In order:" << endl;
  tree->traverseInOrder();

  // Ex 2 - Set up a BST class
  cout << "\nExercise 2: Binary Search Tree" << endl;
  BSTNode *bst = new BSTNode(5);
  bst->insert(3);
  bst->insert(8);
  bst->insert(1);
  bst->insert(9);
  bst->insert(4);
  bst->insert(2);
  bst->insert(6);
  bst->insert(7);
  bst->traverseInOrder();

  // Ex 3 - DFS
  cout << "\nExercise 3: Depth-First Search using a Stack" << endl;
  optional<TreeNode *> dfsResult = dfs(tree, "3");
  if (dfsResult.has_value()) {
    cout << "found " << dfsResult.value()->getContents() << endl;
  } else {
    cout << "coud not find 3" << endl;
  }

  cout << "\nExercise 3a: Depth-First Search using recursion" << endl;
  optional<TreeNode *> dfsRecursiveResult = dfsRecursive(tree, "3");
  if (dfsRecursiveResult.has_value()) {
    cout << "found " << dfsRecursiveResult.value()->getContents() << endl;
  } else {
    cout << "coud not find 3" << endl;
  }

  // Ex 4 - BFS
  cout << "\nExercise 4: Breadth-First Search using a Queue " << endl;
  optional<TreeNode *> bfsResult = bfs(tree, "1");
  if (bfsResult.has_value()) {
    cout << "found " << bfsResult.value()->getContents() << endl;
  } else {
    cout << "coud not find 1" << endl;
  }

  // Ex 5 - AVL tree
  cout << "\nExercise 5: AVL Tree which balances itself" << endl;

  return 0;
}