#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int main() {
    //Print header manually, outside of the text in the file being read from.  This keeps the data being read consistent.
    cout << "\nBelow is a list of the 1000 largest cities in the United States, as of 2013:\n" << endl;
    cout << left << setw(10) << "RANK" << setw(30) << "CITY" << setw(25) << "STATE" << setw(15) << "POPULATION" << right << setw(16) << "GROWTH SINCE 2000" << endl;
    ifstream inFile("uscities.csv");
    //Only proceed with reading and displaying the data if the file was successfully opened.
    if (inFile) {
        //Only read first 1000 lines, to prevent reading the source information at the bottom of the document.
        for (int i = 0; i < 1000; ++i) {
            //Initialize all variables so they can consistently be accessed later in the loop.
            string cityStr, stateStr;
            int rankInt, populationInt;
            double growthDbl;
            char comma, percent;
            inFile >> rankInt >> comma;
            getline(inFile, cityStr, comma);
            getline(inFile, stateStr, comma);
            inFile >> populationInt >> comma;
            inFile >> growthDbl >> percent;
            //Check to make sure stream is not broken as a result of reading errors.  If broken, clear it to continue reading.
            if (!inFile) {
                inFile.clear();
            }
            //TWO TYPES OF OUTPUT MANIPULATION: SETW AND SETFILL:
            cout << setfill('.') << left << setw(10) << rankInt;
            cout << setfill('.') << left << setw(30) << cityStr;
            cout << setfill('.') << left << setw(25) << stateStr;
            cout << setfill('.') << left << setw(15) << populationInt;
            cout << setfill('.') << right << setw(16) << growthDbl << percent << endl;
        }
    }
    inFile.close();
    return 0;
}