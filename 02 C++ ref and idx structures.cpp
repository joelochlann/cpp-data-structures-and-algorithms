#include <iostream>
//#include <algorithm>
//#include <vector>
#include <array>
#include <list>


/* README
*  In this week, we'll take a look at some initial data structures. 
*  We'll contrast indexed based structures (such as arrays and vectors) with memory referenced structures such a linked lists and sequential structures such as streams.
*  
*  There is a random number generator function below which is useful for populating your structures with test data.
*  And below you'll also find the exercise function declarations and class declarations for Link and LinkedList (so they can be defined later). 
*  
*/

using namespace std;

#include <random>

int getRandomNumber() {
    //from C++11 - more reliable than the older C-style srand() function: 
    random_device rd;  // obtain a random seed from the hardware
    mt19937 eng(rd()); // Standard Mersenne Twister engine seeded with rd()
    uniform_int_distribution<int> distribution(1, 100); // distribution from 1 to 100

    int randomNumber = distribution(eng);// generate random number

    return randomNumber;
}


class LinkedList;
class Link;

void exercise1();
void exercise2();
void exercise3();
void exercise4();
void exercise5();

int main() {
    cout << "C++ DS&A Arrays, Vectors and Lists\n" << endl;

    // exercise1();
    // exercise2();
    // exercise3();
    exercise4();
    exercise5();

    return 0;
}


/*
* Exercise 1: Vectors vs arrays
* Create a primitive array of 50 integers. Populate the array with 50 randomly generated values (between the range of 1 to 100). 
* Rather than printing each of the 50 integers, print either the last five values or the total and average of the 50 random values.
* 
* Extension 1: Now replicate this with the STL array. Remember to uncomment the 'include array' above.
* Extension 2: Now replicate this with an STL vector. Likewise, remember to uncomment the 'include vector' statement above.
* Extension 3: Use an iterator to traverse the vector. 
* Question: Is it possible apply an iterator to the STL array too? If so, are there any advantages to applying an iterator here?
*/

void exercise1(){
    cout<< "\n==================\nExercise 1: Arrays and Vectors" << endl;

    const size_t LEN = 50;
    int numbers[LEN];
    for (int i = 0; i < LEN; i++) {
        numbers[i] = getRandomNumber();
    }
    cout << "Last 5: " << endl;
    for (int i = (LEN - 5); i < LEN; i++) {
        cout << numbers[i] << endl;
    }

    int sum = 0;
    int average = 0;
    for (int i; i < LEN; i++) {
        sum += numbers[i];
        average = sum / 50;
    }
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;

    // std::array
    cout << "\n=====\nExtension 1: std::array" << endl;
    array<int, LEN> numbers2;
    for (int i = 0; i < LEN; i++) {
        numbers2[i] = getRandomNumber();
    }
    cout << "Last 5: " << endl;
    for (int i = (LEN - 5); i < LEN; i++)
    {
        cout << numbers2[i] << endl;
    }

    int sum2 = 0;
    int average2 = 0;
    for (int i; i < LEN; i++)
    {
        sum2 += numbers2[i];
        average2 = sum2 / 50;   
    }
    cout << "Sum: " << sum2 << endl;
    cout << "Average: " << average2 << endl;

    // std::vector
    cout << "\n=====\nExtension 2: std::vector" << endl;
    vector<int> intVector;
    for (size_t i = 0; i < LEN; i++)
    {
        intVector.push_back(getRandomNumber());
    }
    cout << "Last 5: " << endl;
    size_t size = intVector.size();

    // Assumes at least 5 elements in vector
    for (size_t i = size - 5; i < size; i++)
    {
        cout << intVector[i] << endl;
    }

    int intVectorSum = 0;
    size_t intVectorAverage = 0;
    for (int el : intVector)
    {
        intVectorSum += el;
        intVectorAverage = intVectorSum / intVector.size();
    }
    cout << "Sum: " << intVectorSum << endl;
    cout << "Average: " << intVectorAverage << endl;

    // Iterator
    vector<int>::iterator it = intVector.begin();
    while (it != intVector.end()) {
        cout << "Element: " << *it << endl;
        it++;
    }

    cout << "==== And again ===" << endl;
    for (int el : intVector)
    {
        cout << "Element: " << el << endl;
    }
}

/*
* Exercise 2: 
* Complete the Link class implementation below, replacing the comments with C++ code.
* then in the exercise2() function underneath, create three link instances with integer data. 
* print this data to the screen via each Link's print function to check that the instances have been created correctly. 
*/

class Link{
    private: 
        int data;
        // Q: is this implicitly NULL, aka 0?
        // Q: better way to do getters and setters?
        Link *next;
        Link *previous;

    public: 
        Link(){} //default constructor 
        Link(int data){ //non-default constructor 
            //assign local 'data' to this Link's data.
            this->data = data;
        }
        void print(){
            //print out the value of this Link's data
            cout << this->data << endl;
        }
        int getData() {
            return this->data;
        }
        Link *getNext() {
            return this->next;
        }
        void setNext(Link *n)
        {
            this->next = n;
        }
        Link *getPrevious()
        {
            return this->previous;
        }
        void setPrevious(Link *n)
        {
            this->previous = n;
        }
};


void exercise2(){
    cout<< "\nExercise 2: Link objects" << endl;

    Link *linkFive = new Link(5);
    Link *linkSeven = new Link(7);
    Link *linkNine = new Link(9);

    linkFive->print();
    linkSeven->print();
    linkNine->print();
}

/*
* Exercise 3: 
* Now complete the LinkedList class below, implementing the prepend (add to the head of the list), find and display functions.
* Test these functions work by adding five Link instances to an instance (object) of the LinkedList.
* 
* Extension 1: Write an append function (add to the tail of the list). 
* Extension 2: Also overload the prepend and append functions to allow integer data values to be passed in 
*              and then 'wrapped' in a Link instance before being added to the Linked List. 
* Extension 3: Write the delete function that will delete a given node 'by-value'.
*              Test this by deleting the start of the list, mid-list and end of the list. 
*/

class LinkedList{
    private:
        Link *head;
        Link *tail;

    public:
        LinkedList(){
            // Q: how to signify end of list?
            // assign 0 to the head of the list by default here
            this->head = NULL;
            this->tail = NULL;
        }
        void display(){
            // traverse the list here by looking each 'next' pointer of a Link instance.
            Link *current = this->head;
            while (current)
            {
                current->print();
                current = current->getNext();
            }
        }
        void prepend(Link* newLink){
            if (this->isEmpty()) {
                this->head = newLink;
                this->tail = newLink;
            } else {
                Link *oldHead = this->head;
                this->head = newLink;
                // Only do this if the list was not previously empty
                // (otherwise we'll segfault when we try and call methods on the null oldHead pointer)
                oldHead->setPrevious(newLink);
                newLink->setNext(oldHead);
            }
        }
        void append(Link* newLink){
            // singly-linked list version (traverse from head):
            // if (this->isEmpty()) {
            //     this->head = newLink;
            //     return;
            // }
            // add a new link instance to the tail of the list.
            // Link *current = this->head;
            // while (current->getNext()) {
            //     current = current->getNext();
            // }
            // // next should be NULL now
            // current->setNext(newLink);

            // New link becomes next of current tail
            // newLink is new tail
            if (this->isEmpty()) {
                this->head = newLink;
                this->tail = newLink;
            } else {
                Link *oldTail = this->tail;
                this->tail = newLink;
                oldTail->setNext(newLink);
                newLink->setPrevious(oldTail);
            }
        }
        Link* find(int valToFind){
            // traverse the list and match the 'valToFind' 
            // with the data attribute in a Link instance.
            // remember to return the pointer to the link that was found, or a null pointer if not found.
            Link *current = this->head;
            while (current) {
                if (current->getData() == valToFind) {
                    return current;
                }
                current = current->getNext();
            }
            return NULL;
        }
        Link* remove(int valToDelete){
            // TODO Q: do we need to deallocate memory??

            // first 'find' the Link instance to delete
            // make sure the Link before the 'one to delete' points to the 'next' of the 'one to delete'. 
            // return the pointer to the link that was deleted, or null pointer if not deleted.

            // Removing the head is a special case
            if (this->head->getData() == valToDelete) {
                Link *nodeToDelete = this->head;
                Link *newHead = nodeToDelete->getNext();
                newHead->setPrevious(NULL);
                if (newHead->getNext()) {
                    newHead->getNext()->setPrevious(newHead);
                } else {
                    // It's now a one-element list
                    this->tail = newHead;
                }
                this->head = newHead;
                return newHead;
            }

            Link *current = this->head;
            while (current && current->getNext()) {
                if (current->getNext()->getData() == valToDelete) {
                    Link *nodeToDelete = current->getNext();
                    
                    if (nodeToDelete == this->tail) {
                        current->setNext(NULL);
                        this->tail = current;
                    } else {
                        current->setNext(nodeToDelete->getNext());
                        current->getNext()->setPrevious(current);
                    }
                    return nodeToDelete;
                }
                current = current->getNext();
            }
            return NULL;
        }
        bool isEmpty(){
            //return true if the LinkedList is empty or false if it contains at least one Link instance.
            if (!this->head) {
                return true;
            }
            return false;
        }
    };


void exercise3(){
    cout<< "\nExercise 3: Linked List operations" << endl;

    LinkedList *ll = new LinkedList();
    ll->prepend(new Link(3));
    ll->prepend(new Link(2));
    ll->prepend(new Link(1));

    ll->append(new Link(4));
    ll->append(new Link(5));
    ll->append(new Link(6));

    ll->display();

    cout << "\n==== ll2 " << endl;
    LinkedList *ll2 = new LinkedList();
    ll2->append(new Link(1));
    ll2->append(new Link(2));
    ll2->append(new Link(3));
    ll2->append(new Link(4));
    ll2->append(new Link(5));
    ll2->append(new Link(6));
    ll2->remove(2);
    ll2->remove(4);
    ll2->remove(1);
    ll2->remove(6);
    ll2->display();
}

/* 
* Exercise 4:  
* Now amend your LinkedList class and your Link class to behave as a 'doubly-linked list'.
* You're advised to add a 'tail' pointer to the LinkedList class (if not already), and a 'previous' pointer into your Link class.
* Amend the prepend/append (insert) methods to also manage 'previous'. Likewise the delete method.
* 
* Extension: Consider if you can amend your find function to traverse the list
*            both forwards and backwards simultaneously, from the head and tail of the list respectivly.
*/

void exercise4(){
    cout<< "\nExercise 4: Doubly Linked List " << endl;

    LinkedList *ll = new LinkedList();
    // cout << "376" << endl;
    ll->prepend(new Link(3));
    // cout << "378" << endl;
    ll->prepend(new Link(2));
    ll->prepend(new Link(1));
    // cout << "387" << endl;
    ll->append(new Link(4));
    ll->append(new Link(5));
    ll->append(new Link(6));
    // cout << "391" << endl;
    ll->display();

    cout << "\n==== ll2 " << endl;
    LinkedList *ll2 = new LinkedList();
    ll2->append(new Link(1));
    ll2->append(new Link(2));
    ll2->append(new Link(3));
    ll2->append(new Link(4));
    ll2->append(new Link(5));
    ll2->append(new Link(6));
    ll2->remove(2);
    ll2->remove(4);
    ll2->remove(1);
    ll2->remove(6);
    ll2->display();
}

/* Exercise 5: STL List vs Linked List 
* 
* By uncommenting and using the 'include list' statement above, implement an STL list. 
* Add five separate integer values by using the 'insert' method. 
* You may also need to specify whether you are 'inserting' at the 'begin' or the 'end of the list.
* 
* Extension 1: Use an iterator to traverse through the STL list. 
* Extension 2: Use the 'find' method from the 'algorithm' class on your STL list.  
*/


void exercise5(){
    
    cout << "Exercise 5: STL List vs Linked List" << endl;

    list<int> l;
    l.insert(l.end(), 1);
    l.insert(l.end(), 2);
    l.insert(l.end(), 3);
    l.insert(l.end(), 4);
    l.insert(l.end(), 5);

    for (auto pos = l.begin(); pos != l.end(); pos++) {
        cout << *pos << endl;
    }
}
