#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>

/* README
 *  In this week, we'll look at Stacks (based on the LIFO principle) and Queues
 * (FIFO principle). We'll set up classes to represent these using arrays,
 * vectors and linked lists. We'll also review the STL stack and queue classes
 * and compare them with ours for good measure! Like before, I've included the
 * exercise function declarations for you to complete the definition for.
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

/* Function to generate a phone number at random by calling the getRandomNumber
 * generator */
/*
long getPhoneNumber(){
    string phoneNum = "447"; // using UK area code +44 and typically they start
with 07 for (int i = 0; i < 9; i++){ phoneNum +=
std::to_string(getRandomNumber(0,9)); //convert the returned int to a str so it
can be appended
    }
    return std::stol(phoneNum); //finally convert the str to a long to return as
a number
}
*/

// below are the class and exercise function declarations

class ArrayStack;   // Exercise 1
class LinkedStack;  // Exercise 2
class Queue;        // Exercise 3
class LinkedQueue;  // Exercise 4
void STLStack();    // Exercise 5
void STLQueue();    // Exercise 5

class ArrayStack {
 private:
  static const size_t MAX_SIZE = 10;
  // define an integer array of MAX_SIZE to store elements
  int elements[MAX_SIZE];
  int top = -1;

 public:
  ArrayStack() {}

  bool isEmpty() { return top == -1; }

  bool isFull() { return top == MAX_SIZE - 1; }

  void push(int item) {
    // The push function should add new data to the top of the stack
    if (!isFull()) {
      elements[++top] = item;
    }
  }

  optional<int> pop() {
    // The pop function should remove data from the top of the stack
    if (isEmpty()) {
      return nullopt;
    }
    return optional<int>{elements[--top]};
  }

  optional<int> peek() {
    // The peek function should return the top of the stack (but not delete)
    if (isEmpty()) {
      return nullopt;
    }
    return optional<int>{elements[top]};
  }
};

/*
 * Exercise 2: Create a Stack that uses a Linked List
 * Now complete the 'LinkedStack' class below, using similiar logic to the
 * 'Stack' class above. However, this time, the pointers to an object of a class
 * will be stacked (pushed) on top of previously added pointers. Code this to be
 * a template class which store objects to pointers of any class.
 *
 * Extension: Function calls and user actions are often stacked on top of each
 * other, often for the purposes of going back/undoing actions. Furthermore,
 * We'll see that the Depth-First Search algorithm stacks nodes on top of each
 * other (and Breadth-First Search algorithm uses queues). For now, simulate a
 * scenario which requires items to be stacked on top of each other. You could
 * add pointers to either functions or objects to this LinkedStack template
 * you've created.
 */

// Make sure you have a Node/Link class defined
// so that pointers to objects of this class can be added to the LinkedStack

class Link {
 private:
  int data;
  // Q: is this implicitly NULL, aka 0?
  // Q: better way to do getters and setters?
  Link *next;

 public:
  Link() {}         // default constructor
  Link(int data) {  // non-default constructor
    // assign local 'data' to this Link's data.
    this->data = data;
  }
  void print() {
    // print out the value of this Link's data
    cout << this->data << endl;
  }
  int getData() { return this->data; }
  Link *getNext() { return this->next; }
  void setNext(Link *n) { this->next = n; }
};

class LinkedStack {
 private:
  Link *top;

 public:
  LinkedStack() {}

  ~LinkedStack() {  // Destructor!
    // Delete all nodes to avoid memory leaks
    while (!isEmpty()) {
      pop();
    }
  }

  bool isEmpty() { return top == NULL; }

  void push(int value) {
    //  Current head becomes next of new head
    // newLink is new head
    Link *newLink = new Link(value);
    Link *oldHead = this->top;

    newLink->setNext(oldHead);
    this->top = newLink;
  }

  int pop() {
    if (!this->top) {
      return -1;
    }
    // The pop function should remove data from the top of the stack
    Link *oldTop = this->top;
    this->top = this->top->getNext();
    int oldValue = oldTop->getData();
    delete oldTop;
    return oldValue;
  }

  int peek() {
    // The peek function should return the top of the stack (but not delete)
    if (!this->top) {
      return -1;
    }
    return this->top->getData();
  }
};

/*
 * Exercise 1: Create a Stack class that uses an Array
 * Complete the Stack class below, which has functionality to 'peek', 'pop', and
 * 'push' data. The push function should add new data to the top of the stack
 * The pop function should remove data from the top of the stack
 * The peek function should return the top of the stack (but not delete)
 *
 * We'll start by representing the stack as an integer array.
 * In main above, populate the stack with random integer values.
 *
 * Extension 1: Either create a new class or amend the Stack class to use a
 * vector rather than an array. Extension 2: Either create a new class or amend
 * the Stack class to be a template class, which can create the stack of a data
 * type specfied when the template class is instantiated.
 *
 */

/*
 * Exercise 3: Create a Queue that uses an Array
 * Using an integer array, complete the class outline below to be able to
 * 'enqueue' and 'dequeue' integer values. The enqueue function should add data
 * to the 'rear' of the queue. The dequeue function should remove data to the
 * 'front' of the queue.
 *
 * Extension 1: Add front and rear 'pointers' so fixed size arrays can be
 * treated as 'circular queue'. Extension 2: Add code to the 'enqueue' function
 * so items are sorted via 'priority'.
 */

class Queue {
 private:
  // declare a constant for the MAX_SIZE of the queue
  static const size_t MAX_SIZE = 10;
  // define an integer array of MAX_SIZE to store elements
  int elements[MAX_SIZE];
  // define an variable that holds the index of the 'front' element
  int front = 0;
  // define an variable that holds the index of the 'rear' element
  int rear = 0;

 public:
  Queue() {}

  bool isEmpty() { return front == rear; }

  bool isFull() { return front == (rear + 1) % MAX_SIZE; }

  void enqueue(int value) {
    // The enqueue function should add data to the 'rear' of the queue.

    // Example:
    // max_size 1, r 0, f 0
    // []
    // not full => set el[0], r becomes 1
    // [1]
    // next enqueue: max_size 1 = r 1, array is full (no-op)
    // cout << "enqueue: " << value << endl;
    // cout << "isFull: " << isFull() << endl;
    if (!isFull()) {
      // cout << "adding at rear: " << rear << endl;
      elements[rear] = value;
      rear = (rear + 1) % MAX_SIZE;
      // cout << "new rear: " << rear << endl;
    }
  }

  int dequeue() {
    // The dequeue function should remove data to the 'front' of the queue.
    // [1, 2]
    if (!isEmpty()) {
      // cout << "removing at front: " << front << endl;
      int ret = elements[front];
      front = (front + 1) % MAX_SIZE;
      // cout << "new front: " << front << endl;
      return ret;
    }
    return -1;
  }

  int peek() {
    // The peek function should return the front of the queue (but not delete)
    return elements[front];
  }
};

/*
 * Exercise 4: Linked Queue
 * Now amend your Queue class and its logic to work a linked list of nodes/links
 * (pointers to objects of any class) You may want to make this a template class
 * so it can handle pointers to objects of any class structure.
 *
 * Extension: If you completed the 'Contacts' class from 04 Hashing, you could
 * model/simulate a 'queue' of customers. (Think trying to phone an energy
 * company!) Generate some customer nodes and add them to a queue (enqueue
 * them). You could 'dequeue' customers after they have been served (you could
 * simulate this by generating random lengths of conversation). Track a given
 * caller's position in the queue (and this should update regularly as customers
 * ahead in the queue are served and exit the queue).
 */

// Make sure you have a Node/Link class defined
// so that pointers to objects of this class can be added to the LinkedStack

class LinkedQueue {
 private:
  // define a pointer to the front of the queue
  Link *front;
  // define a pointer to the rear of the queue
  Link *rear;

 public:
  LinkedQueue() {}

  ~LinkedQueue() {  // Destructor!
    while (!isEmpty()) {
      dequeue();
    }
  }

  bool isEmpty() {
    // check rear too?
    if (!front) {
      return true;
    }
  }

  void enqueue(int value) {
    // Create new link with value
    Link *newLink = new Link(value);
    // Empty is a special case:
    // - set front and rear to new link
    // Otherwise:
    // - new link is new rear
    // - old rear next => new link
    if (isEmpty()) {
      front = rear = newLink;
    } else {
      rear->setNext(newLink);
      rear = newLink;
    }
  }

  int dequeue() {  // feel free to amend the return type
    // The dequeue function should remove data to the 'front' of the queue.
    if (isEmpty()) {
      return -1;
    }
    Link *oldFront = front;
    int ret = oldFront->getData();
    Link *newFront = oldFront->getNext();
    front = newFront;
    delete oldFront;
    return ret;
  }

  int peek() {  // feel free to amend the return type
    // The peek function should return the front of the queue (but not delete)
    if (isEmpty()) {
      return -1;
    }
    return front->getData();
  }
};

/*
 * Exercise 5: STL Stack and Queue
 * Making use of the #include <stack> and #include <queue> commands above,
 * create instances of the STL stack and queue and push/pop data to/from them.
 *
 * Question: Can you identify any differences between STL's Stack and Queue and
 * your classes?
 */

void STLStack() {
  // instantiate the STL stack and push/pop values here.
  stack<int> s;

  s.push(1);
  s.push(2);
  s.push(3);

  // With the STL stack, .pop() does not return the element removed
  int popped;
  while (s.size() > 0) {
    popped = s.top();
    s.pop();
    cout << "Popped " << popped << endl;
  }
}

void STLQueue() {
  queue<int> q;

  q.push(1);
  q.push(2);
  q.push(3);

  // With the STL queue, .pop() does not return the element removed
  int dequeued;
  while (q.size() > 0) {
    dequeued = q.front();
    q.pop();
    cout << "Dequeued " << dequeued << endl;
  }
}

int main() {
  cout << "C++ DS&A Stacks and Queues\n" << endl;

  // Ex 1 - Stack with an array / vector
  cout << "Exercise 1: Stack using an Array / Vector" << endl;
  // instantiate the Stack class and push/pop values here.

  ArrayStack *arrayStack = new ArrayStack();
  cout << "peeked " << arrayStack->peek().value_or(-999) << endl;
  arrayStack->push(1);
  arrayStack->push(2);
  arrayStack->push(3);
  cout << "peeked " << arrayStack->peek().value_or(-999) << endl;
  cout << "popped " << arrayStack->pop().value_or(-999) << endl;
  cout << "popped " << arrayStack->pop().value_or(-999) << endl;
  cout << "popped " << arrayStack->pop().value_or(-999) << endl;
  cout << "popped " << arrayStack->pop().value_or(-999) << endl;
  cout << "popped " << arrayStack->pop().value_or(-999) << endl;

  // Ex 2 - Stack with a Linked List
  cout << "\nExercise 2: Stack using a Linked List " << endl;

  LinkedStack *linkedStack = new LinkedStack();
  cout << "peeked " << linkedStack->peek() << endl;
  linkedStack->push(1);
  linkedStack->push(2);
  linkedStack->push(3);
  cout << "peeked " << linkedStack->peek() << endl;
  cout << "peeked " << linkedStack->peek() << endl;
  cout << "popped " << linkedStack->pop() << endl;
  cout << "popped " << linkedStack->pop() << endl;
  cout << "peeked " << linkedStack->peek() << endl;
  cout << "popped " << linkedStack->pop() << endl;
  cout << "popped " << linkedStack->pop() << endl;
  cout << "popped " << linkedStack->pop() << endl;

  // Ex 3 - Queue using an Array

  cout << "\nExercise 3: Queue using an Array " << endl;
  Queue *queue = new Queue();
  // Seems like we have no way of distinguishing between 0 and uninitialized
  cout << "peeked (empty)" << queue->peek() << endl;
  queue->enqueue(1);
  queue->enqueue(2);
  queue->enqueue(3);
  cout << "dequeue " << queue->dequeue() << endl;
  cout << "dequeue " << queue->dequeue() << endl;
  cout << "dequeue " << queue->dequeue() << endl;
  queue->enqueue(1);
  queue->enqueue(2);
  queue->enqueue(3);
  queue->enqueue(4);
  queue->enqueue(5);
  queue->enqueue(6);
  queue->enqueue(7);
  queue->enqueue(8);
  queue->enqueue(9);
  queue->enqueue(10);
  queue->enqueue(11);
  queue->enqueue(12);
  cout << "dequeue " << queue->dequeue() << endl;
  cout << "dequeue " << queue->dequeue() << endl;
  cout << "dequeue " << queue->dequeue() << endl;
  cout << "dequeue " << queue->dequeue() << endl;
  cout << "dequeue " << queue->dequeue() << endl;
  cout << "dequeue " << queue->dequeue() << endl;
  cout << "dequeue " << queue->dequeue() << endl;
  cout << "dequeue " << queue->dequeue() << endl;
  cout << "dequeue " << queue->dequeue() << endl;
  cout << "dequeue " << queue->dequeue() << endl;
  cout << "dequeue " << queue->dequeue() << endl;
  cout << "dequeue " << queue->dequeue() << endl;
  cout << "dequeue " << queue->dequeue() << endl;


  // instantiate the Queue class and enqueue/dequeue values here.

  // Ex 4 - Queue using a Linked List
  cout << "\nExercise 4: Queue using a Linked List " << endl;
  LinkedQueue *linkedQueue = new LinkedQueue();
  // Seems like we have no way of distinguishing between 0 and uninitialized
  cout << "peeked (empty)" << linkedQueue->peek() << endl;
  cout << "dequeue (empty)" << linkedQueue->dequeue() << endl;
  linkedQueue->enqueue(1);
  linkedQueue->enqueue(2);
  linkedQueue->enqueue(3);
  cout << "dequeue " << linkedQueue->dequeue() << endl;
  cout << "dequeue " << linkedQueue->dequeue() << endl;
  cout << "dequeue " << linkedQueue->dequeue() << endl;
  linkedQueue->enqueue(1);
  linkedQueue->enqueue(2);
  linkedQueue->enqueue(3);
  linkedQueue->enqueue(4);
  linkedQueue->enqueue(5);
  linkedQueue->enqueue(6);
  linkedQueue->enqueue(7);
  linkedQueue->enqueue(8);
  linkedQueue->enqueue(9);
  linkedQueue->enqueue(10);
  linkedQueue->enqueue(11);
  linkedQueue->enqueue(12);
  cout << "dequeue " << linkedQueue->dequeue() << endl;
  cout << "dequeue " << linkedQueue->dequeue() << endl;
  cout << "dequeue " << linkedQueue->dequeue() << endl;
  cout << "dequeue " << linkedQueue->dequeue() << endl;
  cout << "dequeue " << linkedQueue->dequeue() << endl;
  cout << "dequeue " << linkedQueue->dequeue() << endl;
  cout << "dequeue " << linkedQueue->dequeue() << endl;
  cout << "dequeue " << linkedQueue->dequeue() << endl;
  cout << "dequeue " << linkedQueue->dequeue() << endl;
  cout << "dequeue " << linkedQueue->dequeue() << endl;
  cout << "dequeue " << linkedQueue->dequeue() << endl;
  cout << "dequeue " << linkedQueue->dequeue() << endl;
  cout << "dequeue " << linkedQueue->dequeue() << endl;

  // Ex 5 - STL Stack and Queue

  cout << "\nExercise 5: STL Stack Example" << endl;
  STLStack();

  cout << "\nExercise 5: STL Queue Example" << endl;
  STLQueue();

  return 0;
}