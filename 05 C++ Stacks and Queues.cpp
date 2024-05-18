#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <queue>

/* README
*  In this week, we'll look at Stacks (based on the LIFO principle) and Queues (FIFO principle).  
*  We'll set up classes to represent these using arrays, vectors and linked lists. 
*  We'll also review the STL stack and queue classes and compare them with ours for good measure!
*  Like before, I've included the exercise function declarations for you to complete the definition for. 
*  
*/

using namespace std;

#include <random>

// Modified 
int getRandomNumber(int lower, int upper) {
    //from C++11 - more reliable than the older C-style srand() function: 
    random_device rd;  // obtain a random seed from the hardware
    mt19937 eng(rd()); // Standard Mersenne Twister engine seeded with rd()
    uniform_int_distribution<int> distribution(lower, upper); // distribution from lower to upper bound that are passed in

    int randomNumber = distribution(eng);// generate random number

    return randomNumber;
}

/* Function to generate a phone number at random by calling the getRandomNumber generator */
/*
long getPhoneNumber(){
    string phoneNum = "447"; // using UK area code +44 and typically they start with 07
    for (int i = 0; i < 9; i++){
        phoneNum += std::to_string(getRandomNumber(0,9)); //convert the returned int to a str so it can be appended
    }
    return std::stol(phoneNum); //finally convert the str to a long to return as a number
}
*/

// below are the class and exercise function declarations

class ArrayStack;  // Exercise 1
class LinkedStack; // Exercise 2
class Queue;       // Exercise 3
class LinkedQueue; // Exercise 4
void STLStack();   // Exercise 5
void STLQueue();   // Exercise 5

class ArrayStack
{
private:
    static const size_t MAX_SIZE = 10;
    // define an integer array of MAX_SIZE to store elements
    int elements[MAX_SIZE];
    // position where next element would be inserted
    size_t top = 0;

public:
    ArrayStack() {}

    bool isEmpty()
    {
        return top == 0;
    }

    bool isFull()
    {
        return top == MAX_SIZE;
    }

    void push(int item)
    {
        // The push function should add new data to the top of the stack
        if (top < MAX_SIZE)
        {
            elements[top] = item;
            top++;
        }
    }

    int pop()
    {
        // The pop function should remove data from the top of the stack
        if (top > 0)
        {
            int el = elements[top - 1];
            top--;
            return el;
        }
        return NULL;
    }

    int peek()
    {
        // The peek function should return the top of the stack (but not delete)
        if (top > 0)
        {
            return elements[top - 1];
        }
        return NULL;
    }
};

int main() {
    cout << "C++ DS&A Stacks and Queues\n" << endl;

// Ex 1 - Stack with an array / vector 
    cout << "Exercise 1: Stack using an Array / Vector" << endl;
    // instantiate the Stack class and push/pop values here.
    ArrayStack *arrayStack = new ArrayStack();
    arrayStack->push(1);
    arrayStack->push(2);
    arrayStack->push(3);
    cout << "popped " << arrayStack->pop() << endl;
    cout << "popped " << arrayStack->pop() << endl;
    cout << "popped " << arrayStack->pop() << endl;
    cout << "popped " << arrayStack->pop() << endl;
    cout << "popped " << arrayStack->pop() << endl;

    // Ex 2 - Stack with a Linked List
    cout << "\nExercise 2: Stack using a Linked List " << endl;

    // instantiate the LinkedStack class and push/pop nodes here. 


// Ex 3 - Queue using an Array 

    cout << "\nExercise 3: Queue using an Array " << endl;

    // instantiate the Queue class and enqueue/dequeue values here. 


// Ex 4 - Queue using a Linked List
    cout << "\nExercise 4: Queue using a Linked List " << endl;

    // instantiate the LinkedQueue class and enqueue/dequeue values here. 


// Ex 5 - STL Stack and Queue
    
    cout << "\nExercise 5: STL Stack Example" << endl;
    STLStack();

    cout << "\nExercise 5: STL Queue Example" << endl;
    STLQueue();

    return 0;
}

/*
* Exercise 1: Create a Stack class that uses an Array 
* Complete the Stack class below, which has functionality to 'peek', 'pop', and 'push' data.
* The push function should add new data to the top of the stack 
* The pop function should remove data from the top of the stack
* The peek function should return the top of the stack (but not delete)
* 
* We'll start by representing the stack as an integer array. 
* In main above, populate the stack with random integer values. 
* 
* Extension 1: Either create a new class or amend the Stack class to use a vector rather than an array.
* Extension 2: Either create a new class or amend the Stack class to be a template class, which can create the stack 
*              of a data type specfied when the template class is instantiated.
*
*/




/*
* Exercise 2: Create a Stack that uses a Linked List 
* Now complete the 'LinkedStack' class below, using similiar logic to the 'Stack' class above.
* However, this time, the pointers to an object of a class will be stacked (pushed) on top of previously added pointers.
* Code this to be a template class which store objects to pointers of any class. 
* 
* Extension: Function calls and user actions are often stacked on top of each other, often for the purposes of going back/undoing actions. 
*            Furthermore, We'll see that the Depth-First Search algorithm stacks nodes on top of each other (and Breadth-First Search algorithm uses queues).            
*            For now, simulate a scenario which requires items to be stacked on top of each other. You could add pointers to either functions or objects to this LinkedStack template you've created.
*/

// Make sure you have a Node/Link class defined 
// so that pointers to objects of this class can be added to the LinkedStack

class LinkedStack {
private:
    //Define a pointer to the top 'node' of the stack

public:
    LinkedStack(){}

    ~LinkedStack() {  // Destructor! 
        // Delete all nodes to avoid memory leaks
    }

    bool isEmpty() {
        return 0;
    }

    void push(int value) {  //feel free to amend the signature
        //The push function should add new data to the top of the stack 
    }

    int pop() {
        //The pop function should remove data from the top of the stack
        return 0;
    }

    int peek() {
        //The peek function should return the top of the stack (but not delete)
        return 0;
    }
};


/*
* Exercise 3: Create a Queue that uses an Array 
* Using an integer array, complete the class outline below to be able to 'enqueue' and 'dequeue' integer values. 
* The enqueue function should add data to the 'rear' of the queue. 
* The dequeue function should remove data to the 'front' of the queue.
*  
* Extension 1: Add front and rear 'pointers' so fixed size arrays can be treated as 'circular queue'.
* Extension 2: Add code to the 'enqueue' function so items are sorted via 'priority'.   
*/



class Queue {
private:
    // declare a constant for the MAX_SIZE of the queue
    // define an integer array of MAX_SIZE to store elements
    // define an variable that holds the index of the 'front' element
    // define an variable that holds the index of the 'rear' element

public:
    Queue() {}

    bool isEmpty() {
        return 0;
    }

    bool isFull() {
        return 0;
    }

    void enqueue(int value) {
        //The enqueue function should add data to the 'rear' of the queue. 
    }

    int dequeue() {
        //The dequeue function should remove data to the 'front' of the queue.
        return 0;
    }

    int peek() {
        //The peek function should return the front of the queue (but not delete)
        return 0;
    }
};


/*
* Exercise 4: Linked Queue 
* Now amend your Queue class and its logic to work a linked list of nodes/links (pointers to objects of any class)
* You may want to make this a template class so it can handle pointers to objects of any class structure. 
* 
* Extension: If you completed the 'Contacts' class from 04 Hashing, you could model/simulate a 'queue' of customers. 
*            (Think trying to phone an energy company!)  
*            Generate some customer nodes and add them to a queue (enqueue them).
*            You could 'dequeue' customers after they have been served (you could simulate this by generating random lengths of conversation).
*            Track a given caller's position in the queue (and this should update regularly as customers ahead in the queue are served and exit the queue).
*/

// Make sure you have a Node/Link class defined 
// so that pointers to objects of this class can be added to the LinkedStack


class LinkedQueue {
private:
    // define a pointer to the front of the queue
    // define a pointer to the rear of the queue

public:
    LinkedQueue() {}

    ~LinkedQueue() { // Destructor! 
        // Delete all nodes to avoid memory leaks
    }

    bool isEmpty() {
        return 0;
    }

    void enqueue(int value) {  // feel free to amend this signature
        //The enqueue function should add data to the 'rear' of the queue.
    }

    int dequeue() { // feel free to amend the return type
        //The dequeue function should remove data to the 'front' of the queue.
        return 0;
    }

    int peek() { // feel free to amend the return type
        //The peek function should return the front of the queue (but not delete)
        return 0;
    }
};


/* 
* Exercise 5: STL Stack and Queue
* Making use of the #include <stack> and #include <queue> commands above, 
* create instances of the STL stack and queue and push/pop data to/from them. 
*
* Question: Can you identify any differences between STL's Stack and Queue and your classes?
*/

void STLStack(){
    
    // instantiate the STL stack and push/pop values here. 
 
}

void STLQueue(){

    // instantiate the STL queue and enqueue/dequeue values here. 
}