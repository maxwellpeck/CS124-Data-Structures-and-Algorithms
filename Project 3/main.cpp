#include "City.h"
#include "BinarySearchTree.h"
#include "SplayTree.h"
#include "AvlTree.h"

using namespace std;

//======================================================================================================================

//Reads data from file and stores in vector of 1000+ objects.  Vector passed in as address, as required by project specs.
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

//Creates 3 required files containing different orderings of integers.
void integerFiles(vector<City> &cityVector) {
    //Open files
    ofstream intSort("intSort.txt");
    ofstream intRand("intRand.txt");
    ofstream int5("int5.txt");
    if (intSort && int5 && int5) {
        //Create vector for holding all integers, so they can be randomly scrambled.
        vector<int> intVector;

        //! NOTE TO GRADER: Here I manually add intgers to my files to make sure the number of integers
        //! matches the size of my objects vector after dummy objects are created
        //TODO Don't add 3 to cityVector.size() if in the future the 3 dummy objects are removed
        for (int i = 0; i < 3 + cityVector.size(); ++i) {
            //Print integers in order
            intSort << i << "\n";
            //Add integer to vector to be randomly selected in a later loop.
            intVector.push_back(i);
        }
        //Print integers in order, and 5 at a time
        for (int i = 0; i < cityVector.size() / 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                int5 << i << "\n";
            }
        }
        //! NOTE TO GRADER: Here I manually add intgers to my files to make sure the number of integers
        //! matches the size of my objects vector after dummy objects are created
        for (int i = 0; i < 5; ++i) { //TODO Don't add 3 more integers if in the future the 3 dummy objects are removed
            int5 << 1000 << "\n";     //TODO Don't add 3 more integers if in the future the 3 dummy objects are removed
        }                             //TODO Don't add 3 more integers if in the future the 3 dummy objects are removed
        for (int i = 0; i < 5; ++i) { //TODO Don't add 3 more integers if in the future the 3 dummy objects are removed
            int5 << 1001 << "\n";     //TODO Don't add 3 more integers if in the future the 3 dummy objects are removed
        }                             //TODO Don't add 3 more integers if in the future the 3 dummy objects are removed
        for (int i = 0; i < 5; ++i) { //TODO Don't add 3 more integers if in the future the 3 dummy objects are removed
            int5 << 1002 << "\n";     //TODO Don't add 3 more integers if in the future the 3 dummy objects are removed
        }                             //TODO Don't add 3 more integers if in the future the 3 dummy objects are removed
        //Seed value to control random ordering
        srand(3);
        //Holds index of randomly selected integer in intVector
        int randInd;
        //! NOTE TO GRADER: Here I manually add intgers to my files to make sure the number of integers
        //! matches the size of my objects vector after dummy objects are created
        //TODO Don't add 3 to cityVector.size() if in the future the 3 dummy objects are removed
        for (int i = 0; i < 3 + cityVector.size(); ++i) {
            //Generate random integer between 0 and remaining size of vector.
            randInd = static_cast<int>(rand() % intVector.size());
            intRand << intVector[randInd] << "\n";
            intVector.erase(intVector.begin() + randInd);
        }
        intSort.close();
        intRand.close();
        int5.close();
    } else {
        cout << "Problem with integer files" << endl;
    }
}

//======================================================================================================================

void binarySearchTree(const vector<City> &cityVector) {
    //Open integer files
    ifstream intSort("intSort.txt");
    ifstream int5("int5.txt");
    ifstream intRand("intRand.txt");

    //Open files where depths will be recorded
    ofstream bstDepthsSort("bstDepthsSort.txt");
    ofstream bstDepths5("bstDepths5.txt");
    ofstream bstDepthsRand("bstDepthsRand.txt");

    //Initialize and populate tree
    BinarySearchTree<City> bst;
    //! NOTE TO GRADER: Here  I only loop cityVector.size()-3 times to ensure that the 3 dummy objects are left out of tree
    for (int i = 0; i < cityVector.size() - 3; ++i) {
        bst.insert(cityVector[i]);
    }

    //Initialize variables that will hold index values for searching through trees
    //Initialize variables that will store the depth from each search
    int numSort, numRand, num5, depthSort, depthRand, depth5;

    for (int i = 0; i < cityVector.size(); ++i) {
        //Read in index values
        intSort >> numSort;
        intRand >> numRand;
        int5 >> num5;
        depthSort = 0;
        depthRand = 0;
        depth5 = 0;
        //Search for object of specific index and record depth of object
        bst.contains(cityVector[numSort], depthSort);
        bst.contains(cityVector[numRand], depthRand);
        bst.contains(cityVector[num5], depth5);
        //Write to files
        bstDepthsSort << depthSort << "\n";
        bstDepthsRand << depthRand << "\n";
        bstDepths5 << depth5 << "\n";
    }

    //Close files
    intSort.close();
    int5.close();
    intRand.close();
    bstDepthsSort.close();
    bstDepthsRand.close();
    bstDepths5.close();
}

//======================================================================================================================

void avlTree(const vector<City> &cityVector) {
    //Open integer files
    ifstream intSort("intSort.txt");
    ifstream int5("int5.txt");
    ifstream intRand("intRand.txt");

    //Open files where depths will be recorded
    ofstream avlDepthsSort("avlDepthsSort.txt");
    ofstream avlDepths5("avlDepths5.txt");
    ofstream avlDepthsRand("avlDepthsRand.txt");

    //Initialize and populate tree
    AvlTree<City> avl;
    //! NOTE TO GRADER: Here I only loop cityVector.size()-3 times to ensure that the 3 dummy objects are left out of tree
    for (int i = 0; i < cityVector.size() - 3; ++i) {
        avl.insert(cityVector[i]);
    }

    //Initialize variables that will hold index values for searching through trees
    //Initialize variables that will store the depth from each search
    int numSort, numRand, num5, depthSort, depthRand, depth5;

    for (int i = 0; i < cityVector.size(); ++i) {
        //Read in index values
        intSort >> numSort;
        intRand >> numRand;
        int5 >> num5;
        depthSort = 0;
        depthRand = 0;
        depth5 = 0;
        //Search for object of specific index and record depth of object
        avl.contains(cityVector[numSort], depthSort);
        avl.contains(cityVector[numRand], depthRand);
        avl.contains(cityVector[num5], depth5);
        //Write to files
        avlDepthsSort << depthSort << "\n";
        avlDepthsRand << depthRand << "\n";
        avlDepths5 << depth5 << "\n";
    }

    //Close files
    intSort.close();
    int5.close();
    intRand.close();
    avlDepthsSort.close();
    avlDepthsRand.close();
    avlDepths5.close();
}

//======================================================================================================================

void splayTree(const vector<City> &cityVector) {
    //Open integer files
    ifstream intSort("intSort.txt");
    ifstream int5("int5.txt");
    ifstream intRand("intRand.txt");

    //Open files where depths will be recorded
    ofstream splDepthsSort("splDepthsSort.txt");
    ofstream splDepths5("splDepths5.txt");
    ofstream splDepthsRand("splDepthsRand.txt");

    //Initialize and populate multiple splay trees for each integer files
    SplayTree<City> splSort;
    SplayTree<City> splRand;
    SplayTree<City> spl5;
    //! NOTE TO GRADER: Here I only loop cityVector.size()-3 times to ensure that the 3 dummy objects are left out of tree
    for (int i = 0; i < cityVector.size() - 3; ++i) {
        splSort.insert(cityVector[i]);
        splRand.insert(cityVector[i]);
        spl5.insert(cityVector[i]);
    }

    //Initialize variables that will hold index values for searching through trees
    //Initialize variables that will store the depth from each search
    int numSort, numRand, num5, depthSort, depthRand, depth5;

    for (int i = 0; i < cityVector.size(); ++i) {
        //Read in index values
        intSort >> numSort;
        intRand >> numRand;
        int5 >> num5;
        depthSort = 0;
        depthRand = 0;
        depth5 = 0;
        //Search for object of specific index and record depth of object
        splSort.contains(cityVector[numSort], depthSort);
        splRand.contains(cityVector[numRand], depthRand);
        spl5.contains(cityVector[num5], depth5);
        //Write to files
        splDepthsSort << depthSort << "\n";
        splDepthsRand << depthRand << "\n";
        splDepths5 << depth5 << "\n";
    }

    //Close files
    intSort.close();
    int5.close();
    intRand.close();
    splDepthsSort.close();
    splDepthsRand.close();
    splDepths5.close();
}

//======================================================================================================================

int main() {

    //Create Vector
    vector<City> cityVector;

    //Pass address of vector
    readToVector(cityVector);

    //Pass address of vector
    integerFiles(cityVector);

    //! NOTE TO GRADER: Here I manually push back 3 dummy objects to vector, that will not be added to trees
    City dummy1(-1, "dummyObjName1", "dummyObjState1", 68225, -1);
    cityVector.push_back(dummy1);
    City dummy2(-1, "dummyObjName2", "dummyObjState2", 68226, -1);
    cityVector.push_back(dummy2);
    City dummy3(-1, "dummyObjName3", "dummyObjState3", 68227, -1);
    cityVector.push_back(dummy3);

    //Pass address of vector
    binarySearchTree(cityVector);

    //Pass address of vector
    avlTree(cityVector);

    //Pass address of vector
    splayTree(cityVector);

    return 0;
}

//======================================================================================================================