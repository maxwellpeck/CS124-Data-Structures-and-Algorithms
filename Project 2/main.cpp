#include "City.h"

using namespace std;

//======================================================================================================================

//Calculates sum of populations of all 1000 largest cities.  Demonstrated by function call in main(), as required by project specs.
void populationCount(vector<City>* cityVector) {
    int totalPopulation = 0;
    for (int i = 0; i < cityVector->size(); ++i) {
        totalPopulation += (*cityVector)[i].getPopulation();
    }

    //Will display 131132443
    cout << "\nTotal population of all 1000 largest cities: " << totalPopulation << endl;
}

//======================================================================================================================

//Reads data from file and stores in vector of 1000+ objects.  Vector passed in as address, as required by project specs.
void readToVector(vector<City>* cityVector) {
    ifstream inFile("uscities.csv");
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
            cityVector->push_back(city);

            //Check to make sure stream is not broken as a result of reading errors.  If broken, clear it to continue reading.
            if (!inFile) {
                inFile.clear();
            }
            //Below is code using an overloaded operator that displays each city with all field values in the console.
            //cout << (*cityVector)[i] << endl;
        }
    }
    inFile.close();
}

//======================================================================================================================

int main() {
    //Create Vector
    vector<City> cityVector;
    //Pass address of vector
    readToVector(&cityVector);
    //Pass address of vector
    populationCount(&cityVector);
    return 0;
}

//======================================================================================================================