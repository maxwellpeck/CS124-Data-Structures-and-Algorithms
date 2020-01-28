#include <iostream>
#include <vector>

#include "City.h"

using namespace std;

//======================================================================================================================
//Forward Function Declarations

void mergeSort( vector<City> & a, int &mergeSortReads, int &mergeSortWrites );
void mergeSort( vector<City> & a, vector<City> & tmpArray, int left, int right, int &mergeSortReads, int &mergeSortWrites );
void merge( vector<City> & a, vector<City> & tmpArray, int leftPos, int rightPos, int rightEnd, int &mergeSortReads, int &mergeSortWrites );

//----------------------------------------------------------------------------------------------------------------------
//Forward Function Declarations

void percDown( vector<City> & a, int i, int n, int &heapSortReads, int &heapSortWrites );

//======================================================================================================================
  
//Reads data from file and stores in vector of 1000+ o. bjects.  Vector passed in as address, as required by project specs.
void readToVector(vector<City> &cityVector) {
    string dataFileName = "uscities.csv";
    ifstream inFile(dataFileName);
    //Only proceed with reading and displaying the data if the file was successfully opened.

    if (inFile) {
        //Below is the code that prints titles for columns should the data be displayed in the console.
        //cout << left << setw(10) << "RANK" << setw(30) << "CITY" << setw(25) << "STATE" << setw(15) << "POPULATION" << right << setw(16) << "GROWTH SINCE 2000" << endl;
        //Initialize all variables so they can consistently be accessed later in the loop.
        string name, state;
        int populationRank, population;
        double growth;
        char comma, percent;

        //Only read first 1000 lines, to prevent reading the source information at the bottom of the document.
        for (int i = 0; i < 1000; ++i) {
            inFile >> populationRank >> comma;
            getline(inFile, name, comma);
            getline(inFile, state, comma);
            inFile >> population >> comma;
            inFile >> growth >> percent;

            //Create City object to place in vector
            City city(populationRank, name, state, population, growth);
            cityVector.push_back(city);

            //Check to make sure stream is not broken as a result of reading errors.  If broken, clear it to continue reading.
            if (!inFile) {
                inFile.clear();
            }
            //Below is code using an overloaded operator that displays each city with all field values in the console.
            //cout << cityVector[i] << endl;
        }
        inFile.close();
    } else {
        cout << "Problem opening "<< dataFileName << endl;
    }
}

//======================================================================================================================
//Prints Vector of City Objects that is passed as parameter.

void printVector(vector<City> &cityVector) {
    for (const City &c : cityVector) {
        cout << c << endl;
    }
}

//======================================================================================================================
//Clears vector passed as first parameter, and copies the first num elements from the vector passed as the third parameter.

void addFromVector(vector<City> &cityVectorResized, int num, const vector<City> &cityVector) {
    cityVectorResized.clear();
    for (int i = 0; i < num; ++i) {
        cityVectorResized.push_back(cityVector[i]);
    }
}

//======================================================================================================================

void bubbleSort(vector<City> &v, int &bubbleSortReads, int &bubbleSortWrites) {
    bool haveSwapped = true;
    int lastIndex = v.size();
    while (haveSwapped) {
        haveSwapped = false;
        for (int i = 0; i + 1 < lastIndex; ++i) {
            bubbleSortReads += 2;
            if (v[i] > v[i + 1]) {
                // swap the elements
                ++bubbleSortReads;
                City temp = v[i];
                ++bubbleSortWrites;
                ++bubbleSortReads;
                v[i] = v[i + 1];
                ++bubbleSortWrites;
                ++bubbleSortReads;
                v[i + 1] = temp;
                // no comment
                haveSwapped = true;
            }
        }
        --lastIndex;
    }
}

//======================================================================================================================

void insertionSort(vector<City> &v, int &insertionSortReads, int &insertionSortWrites) {
    for (int currentIndex = 1; currentIndex < v.size(); ++currentIndex) {
        ++insertionSortReads;
        City toBeInserted = v[currentIndex];
        int sortedIndex = currentIndex - 1;
        while (sortedIndex >= 0 && toBeInserted < v[sortedIndex]) {
            ++insertionSortReads;
            ++insertionSortWrites;
            ++insertionSortReads;
            v[sortedIndex + 1] = v[sortedIndex];
            --sortedIndex;
        }
        ++insertionSortWrites;
        v[sortedIndex + 1] = toBeInserted;
        //printVector(v);
    }
}

//======================================================================================================================

/**
 * Mergesort algorithm (driver).
 */
void mergeSort( vector<City> & a, int &mergeSortReads, int &mergeSortWrites ) {
    vector<City> tmpArray( a.size( ) );

    mergeSort(a, tmpArray, 0, (a.size( ) - 1), mergeSortReads, mergeSortWrites);
}

/**
 * Internal method that makes recursive calls.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
// Merge Sort has complexity O(N log N)
void mergeSort( vector<City> & a, vector<City> & tmpArray, int left, int right, int &mergeSortReads, int &mergeSortWrites ) {
    if( left < right ) {
        // find the middle index
        // (if there are an odd number of elements, the left half is larger)
        int center = ( left + right ) / 2;
        // recursive calls
        // This part is O(log N)
        mergeSort( a, tmpArray, left, center, mergeSortReads, mergeSortWrites );
        mergeSort( a, tmpArray, center + 1, right, mergeSortReads, mergeSortWrites );
        // then merge the two sorted halves together
        // This part is O(N)
        merge( a, tmpArray, left, center + 1, right, mergeSortReads, mergeSortWrites );
        //printVector(a);
    }
}

/**
 * Internal method that merges two sorted halves of a subarray.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * leftPos is the left-most index of the subarray.
 * rightPos is the index of the start of the second half.
 * rightEnd is the right-most index of the subarray.
 */
void merge( vector<City> & a, vector<City> & tmpArray, int leftPos, int rightPos, int rightEnd, int &mergeSortReads, int &mergeSortWrites ) {
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    // The next three loops combined will copy all elements from
    // the left and right halves into the tmpArray
    // Together, it is one linear step.
    // Main loop
    while( leftPos <= leftEnd && rightPos <= rightEnd ) {
        mergeSortReads += 2;
        if (a[leftPos] <= a[rightPos]) {
            ++mergeSortReads;
            tmpArray[tmpPos++] = move(a[leftPos++]);
        } else {
            ++mergeSortReads;
            tmpArray[tmpPos++] = move(a[rightPos++]);
        }
    }

    while( leftPos <= leftEnd ) {   // Copy rest of first half
        ++mergeSortReads;
        tmpArray[tmpPos++] = move(a[leftPos++]);
    }

    while( rightPos <= rightEnd ) {  // Copy rest of right half
        ++mergeSortReads;
        tmpArray[tmpPos++] = move(a[rightPos++]);
    }

    // This is another linear step to move everything back to the original vector
    // Copy tmpArray back
    for( int i = 0; i < numElements; ++i, --rightEnd ) {
        ++mergeSortWrites;
        a[rightEnd] = move(tmpArray[rightEnd]);
    }
}

//======================================================================================================================

/**
 * Standard heapsort.
 */
void heapSort( vector<City> & a, int &heapSortReads, int &heapSortWrites )
{
    for( int i = a.size( ) / 2 - 1; i >= 0; --i )  /* buildHeap */
        percDown( a, i, a.size( ), heapSortReads, heapSortWrites );
    for( int j = a.size( ) - 1; j > 0; --j )
    {
        heapSortReads += 2;
        heapSortWrites += 2;
        swap( a[ 0 ], a[ j ] );               /* deleteMax */
        percDown( a, 0, j, heapSortReads, heapSortWrites );
    }
}

/**
 * Internal method for heapsort.
 * i is the index of an item in the heap.
 * Returns the index of the left child.
 */
inline int leftChild( int i )
{
    return 2 * i + 1;
}

/**
 * Internal method for heapsort that is used in
 * deleteMax and buildHeap.
 * i is the position from which to percolate down.
 * n is the logical size of the binary heap.
 */
void percDown( vector<City> & a, int i, int n, int &heapSortReads, int &heapSortWrites )
{
    int child;
    City tmp;

    for( tmp = move( a[ i ] ); leftChild( i ) < n; i = child )
    {
        ++heapSortReads;
        child = leftChild( i );
        heapSortReads += 2;
        if( child != n - 1 && a[ child ] < a[ child + 1 ] ) {
            ++child;
        }
        ++heapSortReads;
        if( tmp < a[ child ] ) {
            ++heapSortReads;
            ++heapSortWrites;
            a[i] = move(a[child]);
        }
        else
            break;
    }
    ++heapSortWrites;
    a[ i ] = move( tmp );
}

//======================================================================================================================

void bubbleSortByName(vector<City> &v, int &twoSortReads, int &twoSortWrites) {
    bool haveSwapped = true;
    int lastIndex = v.size();
    while (haveSwapped) {
        haveSwapped = false;
        for (int i = 0; i + 1 < lastIndex; ++i) {
            twoSortReads += 2;
            if (v[i].getName() > v[i + 1].getName()) {
                // swap the elements
                ++twoSortReads;
                City temp = v[i];
                ++twoSortWrites;
                ++twoSortReads;
                v[i] = v[i + 1];
                ++twoSortWrites;
                ++twoSortReads;
                v[i + 1] = temp;
                // no comment
                haveSwapped = true;
            }
        }
        --lastIndex;
    }
}

//======================================================================================================================

int main() {

    //Read 1000 objects to vector.
    vector<City> cityVector;
    readToVector(cityVector);

    //Create vector that will be resized from 100 to 1000 objects for algorithm testing.
    vector<City> cityVectorResized;

    //Initialize all variables
    int bubbleSortReads;
    int bubbleSortWrites;

    int insertionSortReads;
    int insertionSortWrites;

    int mergeSortReads;
    int mergeSortWrites;

    int heapSortReads;
    int heapSortWrites;

    int twoSortReads;
    int twoSortWrites;

    //Loop and inrease i by 100 to test algorithms with vectors from 100 to 1000 objects.
    for (int i = 100; i <= 1000; i += 100) {

        cout << "\n==={SORTING VECTOR OF " << i << " CITY OBJECTS}==========================================================\n" << endl;

        //----------------------------------------------------------------------------------------------------------------------
        //Bubble Sort

        //Clear vetor and push_back i objects for testing.
        addFromVector(cityVectorResized, i, cityVector);

        bubbleSortReads = 0;
        bubbleSortWrites = 0;

        bubbleSort(cityVectorResized, bubbleSortReads, bubbleSortWrites);

        cout << "bubbleSortReads: " << bubbleSortReads << endl;
        cout << "bubbleSortWrites: " << bubbleSortWrites << endl << endl;

        //----------------------------------------------------------------------------------------------------------------------
        //Insertion Sort

        //Clear vetor and push_back i objects for testing.
        addFromVector(cityVectorResized, i, cityVector);

        insertionSortReads = 0;
        insertionSortWrites = 0;

        insertionSort(cityVectorResized, insertionSortReads, insertionSortWrites);

        cout << "insertionSortReads: " << insertionSortReads << endl;
        cout << "insertionSortWrites: " << insertionSortWrites << endl << endl;

        //----------------------------------------------------------------------------------------------------------------------
        //Merge Sort

        //Clear vetor and push_back i objects for testing.
        addFromVector(cityVectorResized, i, cityVector);

        mergeSortReads = 0;
        mergeSortWrites = 0;

        mergeSort(cityVectorResized, mergeSortReads, mergeSortWrites);

        cout << "mergeSortReads: " << mergeSortReads << endl;
        cout << "mergeSortWrites: " << mergeSortWrites << endl << endl;

        //----------------------------------------------------------------------------------------------------------------------
        //Heap Sort

        //Clear vetor and push_back i objects for testing.
        addFromVector(cityVectorResized, i, cityVector);

        heapSortReads = 0;
        heapSortWrites = 0;

        heapSort(cityVectorResized, heapSortReads, heapSortWrites);

        cout << "heapSortReads: " << heapSortReads << endl;
        cout << "heapSortWrites: " << heapSortWrites << endl << endl;

        //----------------------------------------------------------------------------------------------------------------------
        //Two-Sort

        //Clear vetor and push_back i objects for testing.
        addFromVector(cityVectorResized, i, cityVector);

        twoSortReads = 0;
        twoSortWrites = 0;

        insertionSort(cityVectorResized, twoSortReads, twoSortWrites);

        bubbleSortByName(cityVectorResized, twoSortReads, twoSortWrites);

        cout << "twoSortReads: " << twoSortReads << endl;
        cout << "twoSortWrites: " << twoSortWrites << endl;

        //----------------------------------------------------------------------------------------------------------------------
    }

    return 0;

}