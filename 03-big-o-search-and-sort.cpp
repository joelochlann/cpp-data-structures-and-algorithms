#include <chrono>  // for the high_resolution_clock function
#include <iostream>

/* README
 *  In this week, we'll compare the performance of different search and sorting
 * algorithms.
 *
 *  There is a random number generator function below which is useful for
 * populating your structures with test data. I've also included code to time
 * the duration of these functions, using the 'high_resolution_clock' function
 * of the 'chrono' library. Like before, I've included the exercise function
 * declarations for you to complete the definition for.
 *
 */

using namespace std;

#include <random>

int getRandomNumber() {
  // from C++11 - more reliable than the older C-style srand() function:
  random_device rd;   // obtain a random seed from the hardware
  mt19937 eng(rd());  // Standard Mersenne Twister engine seeded with rd()
  uniform_int_distribution<int> distribution(
      1, 100);  // distribution from 1 to 100

  int randomNumber = distribution(eng);  // generate random number

  return randomNumber;
}

// below are the exercise function declarations

void initArray(int arr[], int size);                  // Exercise 1
void bubbleSort(int arr[], int size);                 // Exercise 2
void mergeSort(int arr[], size_t size);       // Exercise 3
void merge(int arr[], int left, int mid, int right);  // Exercise 3
int linearSearch(int arr[], int size, int target);    // Exercise 4
int binarySearch(int arr[], int size, int target);    // Exercise 5

void print(int arr[], int size) {
  cout << "[";
  for (int i = 0; i < size; i++) {
    cout << arr[i];
    if (i < (size - 1)) {
      cout << ", ";
    }
  }
  cout << "]" << endl;
}

bool isSorted(int arr[], int size) {
  if (size == 0 || size == 1) {
    return true;
  }
  for (int i = 1; i < size; i++) {
    if (arr[i] < arr[i - 1]) {
      return false;
    }
  }
  return true;
}

double timeSort(void (*sortFunc)(int[], size_t), size_t size) {
  int *arr = new int[size];
  initArray(arr, size);
  if (isSorted(arr, size)) {
    cout << "Before sort: array is sorted!!" << endl;
  } else {
    cout << "Before sort: array is not sorted" << endl;
  }
  auto start = chrono::high_resolution_clock::now();
  sortFunc(arr, size);
  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double> duration = end - start;

  if (isSorted(arr, size)) {
    cout << "After sort: array is sorted" << endl;
  } else {
    cout << "After sort: array is not sorted!!" << endl;
  }
  cout << "Elapsed time for " << size << " elements: " << duration.count()
       << " seconds\n";
  return duration.count();
}

void compareSortTime(void (*sortFunc)(int[], size_t), size_t size1,
                     size_t size2) {
  double time1 = timeSort(sortFunc, size1);
  double time2 = timeSort(sortFunc, size2);
  cout << "Ratio between array sizes: " << size2 / size1 << endl;
  cout << "Ratio between search times: " << time2 / time1 << endl;
}

double timeSearch(int (*searchFunc)(int[], size_t, int), size_t size,
                  int target) {
  int *arr = new int[size];
  initArray(arr, size);
  mergeSort(arr, size);
  auto start = chrono::high_resolution_clock::now();
  int foundIndex = searchFunc(arr, size, target);
  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double> duration = end - start;
  if (foundIndex == -1) {
    cout << "Target not found" << endl;
  } else {
    cout << "Found target at index " << foundIndex << endl;
  }
  cout << "Elapsed time for " << size << " elements: " << duration.count()
       << " seconds\n";
  return duration.count();
}

void compareSearchTime(int (*searchFunc)(int[], size_t, int), size_t size1,
                       size_t size2, int target) {
  double time1 = timeSearch(searchFunc, size1, target);
  double time2 = timeSearch(searchFunc, size2, target);
  cout << "Ratio between array sizes: " << size2 / size1 << endl;
  cout << "Ratio between sort times: " << time2 / time1 << endl;
}

/*
 * Exercise 1: Completing the initArray function below which takes a pointer to
 * an array and the size to iterate through. Write a loop which iterate through
 * the array (being pointed to) and assign random values (using the
 * getRandomNumber function above) for each element. You should code the
 * function in a way that can be reused for different array sizes.
 */

void initArray(int arr[], int size) {
  cout << "Initialising an array of size " << size << endl;
  for (int i = 0; i < size; i++) {
    //*(arr + i) = getRandomNumber();
    arr[i] = getRandomNumber();
  }
}

/*
 * Exercise 2:
 * Implement a Bubble Sort algorithm in the function below.
 * Pass both the small and large arrays to this function and time how long each
 * takes.
 *
 * Extension: are there any ways to optimise this bubble sort function?
 * Compare the time of the optimised against the unoptimised original algorithm
 */

void swap(int *a, int *b) {
  int *temp;
  temp = b;
  b = a;
  a = temp;
}

void bubbleSort(int arr[], size_t size) {
  cout << "Bubble sorting an array of size " << size << endl;

  bool swapped;
  do {
    swapped = false;
    for (int i = 0; i < (size - 1); i++) {
      if (arr[i] > arr[i + 1]) {
        swap(arr[i], arr[i + 1]);
        swapped = true;
      }
    }
  } while (swapped);
}

/*
 * Exercise 3: Provided the 'merge' logic below, complete the 'merge sort'
 * function to complete the algorithm. Once complete, comment out your 'exercise
 * 2 bubble sort function calls' and instead call merge sort on the small and
 * large arrays.
 *
 * Extension : If you have 'time', why not increase the size of the 'largeArray'
 * by an appropriate interval (e.g. another 100000) and observe the time
 * difference between bubble sort and merge sort algorithms. What do you notice?
 */

void mergeSortRecurse(int arr[], int left, int right) {
  if (left == right) {
    return;
  }
  // Gets rounded down
  int mid = (left + right) / 2;

  // Sort left
  mergeSortRecurse(arr, left, mid);

  // Sort right
  mergeSortRecurse(arr, mid + 1, right);

  // Merge
  merge(arr, left, mid, right);
}

void mergeSort(int arr[], size_t size) {  // right will be size-1
  cout << "Merge sorting an array of size " << size << endl;
  mergeSortRecurse(arr, 0, size - 1);
}

// merge given here to save time
void merge(int arr[], int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  int L[n1], R[n2];

  for (int i = 0; i < n1; ++i) {
    L[i] = arr[left + i];
  }
  for (int j = 0; j < n2; ++j) {
    R[j] = arr[mid + 1 + j];
  }

  int i = 0, j = 0, k = left;

  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      ++i;
    } else {
      arr[k] = R[j];
      ++j;
    }
    ++k;
  }

  while (i < n1) {
    arr[k] = L[i];
    ++i;
    ++k;
  }

  while (j < n2) {
    arr[k] = R[j];
    ++j;
    ++k;
  }
}

/*
 * Exercise 4: Implement the Linear Search algorithm below.
 * To start, just check that you can find a value that is in an array (positive
 * case). Also check the negative case - where a value isn't in the array.
 *
 * In the next exercise, we will compare the speed of linear and binary search
 * for locating the same element.
 *
 */

int linearSearch(int arr[], size_t size, int target) {
  cout << "Linear Search of array of size " << size
       << " to locate value " << target << endl;

  for (int i = 0; i < size; i++) {
    if (arr[i] == target) {
      return i;
    }
  }

  return -1;
}

/* Exercise 5: Now implement the binary search function below.
 * For comparing the time taken to find values, find ensure the small and large
 * arrays are sorted (either sort algorithm). Then select values at the start,
 * mid and end of the list to pass to both binary and linear search run on the
 * SAME array.
 *
 * Note: You could modify the signature to pass in left and right,
 * but as left is usually initialised to 0, and right to size-1,
 * this can be infered from size being passed in.
 *
 * Extension : Can you modify the algorithm to not just return/print the first
 * instance of a value, but count (and/or index positions) of each instance of
 * this value in the structure.
 */

int binarySearch(int arr[], size_t size, int target) {
  cout << "Binary Search of array of size " << size
       << " to locate value " << target << endl;

  int start = 0;
  int end = size - 1;

  while (end >= start) {
    // rounded down
    int mid = (start + end) / 2;
    if (mid == target) {
      return mid;
    }
    if (mid < target) {
      start = mid + 1;
    } else {
      end = mid;
    }
  }
  return -1;
}

int main() {
  cout << "C++ DS&A Big O + Search and Sorting algorithms\n" << endl;

  cout << "\nExercise 1: Initialise an array" << endl;
  // TODO: timing and logging for something linear (initialising arrays)
  int *smallArray = new int[100];
  initArray(smallArray, 100);

  // cout << "\nExercise 2: Bubble sort" << endl;
  // compareSortTime(&bubbleSort, 1000, 10000);

  // cout << "\nExercise 3: Merge Sort" << endl;
  // compareSortTime(&mergeSort, 100000, 2000000);

  cout << "\nExercise 3: Linear search" << endl;
  compareSearchTime(&linearSearch, 10000, 1000000, 101);
  cout << endl;
  compareSearchTime(&linearSearch, 10000, 100000, 34);

  /* Exercise 5 - Binary Search */
  cout << "\nExercise 5: Binary Search" << endl;
  compareSearchTime(&binarySearch, 10000, 1000000, 101);
  cout << endl;
  compareSearchTime(&binarySearch, 10000, 100000, 34);

  return 0;
}