#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>

/* README
*  In this week, we'll look at hashing algorithms. 
*  We'll attempt to model a phone contacts app, in which users can look up a phone number by a person's name.
* 
*  There is a random number generator function below which is useful for populating your structures with test data.
*  I've modified the signature to accept a lower and upper bound. 
*  This is so we can call this method to generate a random UK phone number - modify the format to your area code if you wish! 
*  Like before, I've included the exercise function declarations for you to complete the definition for. 
*  
*/

using namespace std;

#include <random>

/* Modified */
int getRandomNumber(int lower, int upper) {
    //from C++11 - more reliable than the older C-style srand() function: 
    random_device rd;  // obtain a random seed from the hardware
    mt19937 eng(rd()); // Standard Mersenne Twister engine seeded with rd()
    uniform_int_distribution<int> distribution(lower, upper); // distribution from lower to upper bound that are passed in

    int randomNumber = distribution(eng);// generate random number

    return randomNumber;
}

/* Function to generate a phone number at random by calling the getRandomNumber generator */
long getPhoneNumber(){
    string phoneNum = "447"; // using UK area code +44 and typically they start with 07
    for (int i = 0; i < 9; i++){
        phoneNum += std::to_string(getRandomNumber(0,9)); //convert the returned int to a str so it can be appended
    }
    return std::stol(phoneNum); //finally convert the str to a long to return as a number
}

// below are the exercise function declarations

int hash_(long key, int tableSize); //Exercise 1
int hash_(const string& key, int tableSize); //Exercise 2

void addressing(); //Exercise 3  - feel free to modify this

class HashTable; //Exercise 4
class LinkedList; //Exercise 4 
class Contact; //Exercise 4 - representing the Person's name and phone number

void unorderedMap(); // Exercise 5



/*
* Exercise 1: Set up the hash table
* 
* In Main above, replace the comments with code to set up the hashTable. 
* Then complete the hash_ function below which uses the 'division method' 
* to return an unique index value based on the key and tablesize passed in.
* Once ready, in main, call the 'getPhoneNumber()' function, which for this example, will act as the 'key' (and value).
* Then pass this 'key' to the hash_ function (along with tableSize) to return a unique index in which to store the phone number. 
* You should then assign the phone number to the hashTable in main at the index returned by hash_.
* 
* Check this has been assigned correctly by uncommenting the call to the hash_ function within the subscript operator of the hashTable. 
*  
* Note: the name 'hash_' was chosen to not interfere with preset functions called 'hash'
*
*/

int hash_(long key, int tableSize) {
    // Exercise 1: implement your solution here. 
    return 0;
}

/*
* Exercise 2: String hashing
* So now, let's choose a more meaningful key - a string which represents a name of a contact
* You should see an overloaded 'hash_()' function below which takes a string as the key, in addition to the tableSize.
* In this function, code an algorithm that will formulate a unique index position 
* based up on the ASCII values of each character in the string key.
* Return this unique index and test that you can add a phone number for a name of a person to the HashTable, as well as retrieve it.
* 
* Extension: Try adding a handful of names and phone numbers checking you can retreive the right number for the right person. 
*/


int hash_(const string& key, int tableSize) {
    // Exercise 2 - implement your solution here. 
    return 0;
}


/*
* Exercise 3: Open Addressing with probing techniques 
* To illustrate a collision, in main above, attempt to hash an identical name. This should return an indentical index value.
* You should notice that a new random phone number has been assigned, overwriting the previously stored number. 
* One method to resolve collisions like this would be to use open addressing. 
* You could ammend the two hash functions that you have, or you could code a strategy in a function below, which is then called in both hash_ functions
* Try linear, quadratic and prime probing strategies.
* 
* In main, test that you can retrieve the right number for the adjusted position 
* calculated by the probing strategies.
*/

void addressing(){
    //implement your solution here

}

/* Exercise 4: Closed chaining 
* The other approach to resolving collisions could be to create a structured within the hashTable itself. 
* Now, because we've set up a array of primitive integers, it's not going to take 
* Therefore, consider how you could set up a wrapper class for your 'HashTable' which makes use of your LinkedList class
* or alternatively to a LinkedList, you could use a vector instead. 
*
* Add as many classes and/or functions as you need.  
*
* Question: what are the benefits and drawbacks of each approach? Which situations are they most suitable? 
*/

class Contact{
    public: 
        string name;
        long phoneNum;

        Contact(){}
        Contact(string name, long phoneNum){
            this->name = name;
            this->phoneNum = phoneNum;
        } 
        // complete the rest... 
};

class HashTable{
    public: 
        Contact** hashTable; // pointer to a pointer
        int size = 30; // default

        HashTable(){}
        HashTable(int size){ //could pass in the size here
            this->size = size;
            hashTable = new Contact*[size]; //array of Contact pointers - so you can chain at colliding positions
        }

    // complete the rest... 
};

class LinkedList{
    public: 
        Contact* head;
        Contact* tail; 
        
    // complete the rest... 
};


/* 
* Exercise 5: STL Unordered Map
* 
* Finally, to finish off, create an instance of an STL unordered_map.
* Declare your instance to take a string key and an integer value. 
* Try to replace the above tests of people and contact numbers.  
* 
* Question: Are collisions a problem? How does the STL Map resolve them?
* Question: How does the performance of this STL map compare with our hash tables?  
*/

void unorderedMap(){
    cout<< "\nExercise 5: STL Unordered Map" << endl;
    //implement your solution here. 

}

int main() {
  cout << "C++ DS&A Hashing\n" << endl;

  // Ex 1
  // Declare a constant for the TABLE_SIZE of 30
  long*
      hashTable;  // Declare a pointer to an array of TABLE_SIZE. Use the data
                  // type 'long' to be able to handle 11-12 digit phone numbers.

  cout << "Exercise 1: Hash Function for integer keys" << endl;

  // call the 'getPhoneNumber' here and assign return to 'key'
  // then pass the key and TABLE_SIZE to the hash_ function - assign the return
  // to an index variable hashTable[index] = key;

  /* Check your hash worked correctly by uncommenting the below statement */
  // cout << "The hash of key " << key << " is " << index << " which stores the
  // value " << hashTable[hash_(key, TABLE_SIZE)] << endl;

  // Ex 2
  cout << "\nExercise 2: Overloaded Hash Function for string keys" << endl;

  // assign your name as a key and call the overloaded hash function
  /*
      string stringKey = "Nick"; //now assign a name of a person as a string key
      key = getPhoneNumber();
      index = hash_(stringKey, TABLE_SIZE); //call the string overload of the
     hash_ function here hashTable[index] = key;

      cout << "The hash of key " << stringKey << " is " << index << " which
     stores the value " << hashTable[hash_(stringKey, TABLE_SIZE)] << endl;
  */

  // Ex 3 - open addressing - try linear probing, quadratic probing, and prime
  // probing (aka double hashing)

  cout << "\nExercise 3: Collisions - Open Addressing " << endl;

  // attempt to add another duplicate name here...
  /*
      string stringKeyDup = "Nick";
      key = getPhoneNumber();
      index = hash_(stringKeyDup, TABLE_SIZE);
      hashTable[index] = key;

      cout << "The hash of key " << stringKeyDup << " is " << index << " which
     stores the value " << hashTable[hash_(stringKeyDup, TABLE_SIZE)] << endl;
  */

  // Ex 4 - closed chaining with a wrapper for the HashTable, which instantiates
  // a LinkedList with colliding elements

  // Ex 5 - now finally utilise the unordered_map - compare its performance
  // against previous hash tables.

  return 0;
}