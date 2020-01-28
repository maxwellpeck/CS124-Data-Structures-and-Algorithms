#include <iostream>
#include <vector>

#include "City.h"
#include "SeparateChaining.h"
#include "Probing.h"

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

string getName1(City city) {
    return city.getName();
}

//======================================================================================================================

string getName2(City city) {
    return city.getName() + "APPEND TO STRING";
}

//======================================================================================================================

void sepChain(vector<City> &cityVector) {

    cout << endl << "=========================================================================================" << endl;

    cout << endl << "Separate Chaining Insert reads with City Name as key:" << endl;

    int numSepChainReads = 0;
    SeparateChaining<City> hashTableSep1(cityVector.size(), getName1);
    for (City &city : cityVector) {
        hashTableSep1.insert(city, numSepChainReads);
    }
    cout << "Separate Chaining Insert Reads (Table Size = 1000): " << numSepChainReads << endl;

    numSepChainReads = 0;
    SeparateChaining<City> hashTableSep2(997, getName1);
    for (City &city : cityVector) {
        hashTableSep2.insert(city, numSepChainReads);
    }
    cout << "Separate Chaining Insert Reads (Table Size = 997): " << numSepChainReads << endl;

    numSepChainReads = 0;
    SeparateChaining<City> hashTableSep3(991, getName1);
    for (City &city : cityVector) {
        hashTableSep3.insert(city, numSepChainReads);
    }
    cout << "Separate Chaining Insert Reads (Table Size = 991): " << numSepChainReads << endl;

    numSepChainReads = 0;
    SeparateChaining<City> hashTableSep4(853, getName1);
    for (City &city : cityVector) {
        hashTableSep4.insert(city, numSepChainReads);
    }
    cout << "Separate Chaining Insert Reads (Table Size = 853): " << numSepChainReads << endl;

    numSepChainReads = 0;
    SeparateChaining<City> hashTableSep5(379, getName1);
    for (City &city : cityVector) {
        hashTableSep5.insert(city, numSepChainReads);
    }
    cout << "Separate Chaining Insert Reads (Table Size = 379): " << numSepChainReads << endl;

    //------------------------------------------------------------------------------------------------------------------

    cout << endl << "Insert reads with City Name as key, appended with string \"APPEND TO STRING\" (More Characters in Key):" << endl;

    numSepChainReads = 0;
    SeparateChaining<City> hashTableSep12(cityVector.size(), getName2);
    for (City &city : cityVector) {
        hashTableSep12.insert(city, numSepChainReads);
    }
    cout << "Separate Chaining Insert Reads (Table Size = 1000): " << numSepChainReads << endl;

    numSepChainReads = 0;
    SeparateChaining<City> hashTableSep22(997, getName2);
    for (City &city : cityVector) {
        hashTableSep22.insert(city, numSepChainReads);
    }
    cout << "Separate Chaining Insert Reads (Table Size = 997): " << numSepChainReads << endl;

    numSepChainReads = 0;
    SeparateChaining<City> hashTableSep32(991, getName2);
    for (City &city : cityVector) {
        hashTableSep32.insert(city, numSepChainReads);
    }
    cout << "Separate Chaining Insert Reads (Table Size = 991): " << numSepChainReads << endl;

    numSepChainReads = 0;
    SeparateChaining<City> hashTableSep42(853, getName2);
    for (City &city : cityVector) {
        hashTableSep42.insert(city, numSepChainReads);
    }
    cout << "Separate Chaining Insert Reads (Table Size = 853): " << numSepChainReads << endl;

    numSepChainReads = 0;
    SeparateChaining<City> hashTableSep52(379, getName2);
    for (City &city : cityVector) {
        hashTableSep52.insert(city, numSepChainReads);
    }
    cout << "Separate Chaining Insert Reads (Table Size = 379): " << numSepChainReads << endl;

    //------------------------------------------------------------------------------------------------------------------

//    cout << endl << "Search for City \"Burlington, Vermont\":" << endl;
//
//    numSepChainReads = 0;
//    hashTableSep1.search("Burlington", cityVector[871], numSepChainReads);
//    cout << "Separate Chaining Search Reads (Table Size = 1000): " << numSepChainReads << endl;

    //------------------------------------------------------------------------------------------------------------------

//    cout << endl << "Remove City \"Burlington, Vermont\":" << endl;
//
//    numSepChainReads = 0;
//    hashTableSep1.remove("Burlington", numSepChainReads);
//    cout << "Separate Chaining Remove Reads (Table Size = 1000): " << numSepChainReads << endl;

}

//======================================================================================================================

void linProbe(vector<City> &cityVector) {

    cout << endl << "=========================================================================================" << endl;

    cout << endl << "Linear Probing Insert reads with City Name as key:" << endl;

    int numLinProbingReads = 0;
    Probing<City> hashTableProbe1(cityVector.size(), getName1);
    for (City &city : cityVector) {
        hashTableProbe1.insert(city, numLinProbingReads);
    }
    cout << "Linear Probing Insert Reads (Starting Table Size = 1000): " << numLinProbingReads << endl;
    cout << "Ending Table Size after Insertion: " << hashTableProbe1.getTableSize() << endl;

    numLinProbingReads = 0;
    Probing<City> hashTableProbe2(997, getName1);
    for (City &city : cityVector) {
        hashTableProbe2.insert(city, numLinProbingReads);
    }
    cout << "Linear Probing Insert Reads (Starting Table Size = 997): " << numLinProbingReads << endl;
    cout << "Ending Table Size after Insertion: " << hashTableProbe2.getTableSize() << endl;

    numLinProbingReads = 0;
    Probing<City> hashTableProbe3(991, getName1);
    for (City &city : cityVector) {
        hashTableProbe3.insert(city, numLinProbingReads);
    }
    cout << "Linear Probing Insert Reads (Starting Table Size = 911): " << numLinProbingReads << endl;
    cout << "Ending Table Size after Insertion: " << hashTableProbe3.getTableSize() << endl;

    numLinProbingReads = 0;
    Probing<City> hashTableProbe4(853, getName1);
    for (City &city : cityVector) {
        hashTableProbe4.insert(city, numLinProbingReads);
    }
    cout << "Linear Probing Insert Reads (Starting Table Size = 853): " << numLinProbingReads << endl;
    cout << "Ending Table Size after Insertion: " << hashTableProbe4.getTableSize() << endl;

    numLinProbingReads = 0;
    Probing<City> hashTableProbe5(379, getName1);
    for (City &city : cityVector) {
        hashTableProbe5.insert(city, numLinProbingReads);
    }
    cout << "Linear Probing Insert Reads (Starting Table Size = 379): " << numLinProbingReads << endl;
    cout << "Ending Table Size after Insertion: " << hashTableProbe5.getTableSize() << endl;

    //------------------------------------------------------------------------------------------------------------------

    cout << endl << "Linear Probing Insert reads with City Name as key, appended with string \"APPEND TO STRING\" (More Characters in Key):" << endl;

    numLinProbingReads = 0;
    Probing<City> hashTableProbe12(cityVector.size(), getName2);
    for (City &city : cityVector) {
        hashTableProbe12.insert(city, numLinProbingReads);
    }
    cout << "Linear Probing Insert Reads (Starting Table Size = 1000): " << numLinProbingReads << endl;
    cout << "Ending Table Size after Insertion: " << hashTableProbe12.getTableSize() << endl;

    numLinProbingReads = 0;
    Probing<City> hashTableProbe22(997, getName2);
    for (City &city : cityVector) {
        hashTableProbe22.insert(city, numLinProbingReads);
    }
    cout << "Linear Probing Insert Reads (Starting Table Size = 997): " << numLinProbingReads << endl;
    cout << "Ending Table Size after Insertion: " << hashTableProbe22.getTableSize() << endl;

    numLinProbingReads = 0;
    Probing<City> hashTableProbe32(991, getName2);
    for (City &city : cityVector) {
        hashTableProbe32.insert(city, numLinProbingReads);
    }
    cout << "Linear Probing Insert Reads (Starting Table Size = 911): " << numLinProbingReads << endl;
    cout << "Ending Table Size after Insertion: " << hashTableProbe32.getTableSize() << endl;

    numLinProbingReads = 0;
    Probing<City> hashTableProbe42(853, getName2);
    for (City &city : cityVector) {
        hashTableProbe42.insert(city, numLinProbingReads);
    }
    cout << "Linear Probing Insert Reads (Starting Table Size = 853): " << numLinProbingReads << endl;
    cout << "Ending Table Size after Insertion: " << hashTableProbe42.getTableSize() << endl;

    numLinProbingReads = 0;
    Probing<City> hashTableProbe52(379, getName2);
    for (City &city : cityVector) {
        hashTableProbe52.insert(city, numLinProbingReads);
    }
    cout << "Linear Probing Insert Reads (Starting Table Size = 379): " << numLinProbingReads << endl;
    cout << "Ending Table Size after Insertion: " << hashTableProbe52.getTableSize() << endl;

    //------------------------------------------------------------------------------------------------------------------

//    cout << endl << "Remove City \"Burlington, Vermont\":" << endl;
//
//    numLinProbingReads = 0;
//    hashTableProbe1.remove("Burlington", numLinProbingReads);
//    cout << "Linear Probing Remove Reads (Table Size = 1000): " << numLinProbingReads << endl;

}

//======================================================================================================================

int main() {

    vector<City> cityVector;
    readToVector(cityVector);
    sepChain(cityVector);
    linProbe(cityVector);

    return 0;

}