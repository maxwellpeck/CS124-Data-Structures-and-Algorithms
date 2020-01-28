//
// Created by Maxwell Peck on 2/25/18.
//

#ifndef PROJECT_2_CITY_H
#define PROJECT_2_CITY_H

#include <iomanip>
#include <fstream>
#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;

class City {
private:
    int populationRank;
    string name;
    string state;
    int population;
    double growth;
public:
    /**
     * Default Constructor
     * Requires: Nothing
     * Modifies: populationRank, name, state, population, growth
     * Effects: Constructs City with populationRank 0, name "City," state "State," population 0, and growth 0.
    */
    City();

    /**
     * Non-Default Constructor
     * Requires: Nothing
     * Modifies: populationRank, name, state, population, growth
     * Effects: Constructs City with populationRank popRank, name "City," state "State," population 0, and growth 0.
    */
    City(int popRank);

    /**
     * Non-Default Constructor
     * Requires: Nothing
     * Modifies: populationRank, name, state, population, growth
     * Effects: Constructs City with populationRank popRank, name nm, state "State," population 0, and growth 0.
    */
    City(int popRank, string nm);

    /**
     * Non-Default Constructor
     * Requires: Nothing
     * Modifies: populationRank, name, state, population, growth
     * Effects: Constructs City with populationRank popRank, name nm, state st, population 0, and growth 0.
    */
    City(int popRank, string nm, string st);

    /**
     * Non-Default Constructor
     * Requires: Nothing
     * Modifies: populationRank, name, state, population, growth
     * Effects: Constructs City with populationRank popRank, name nm, state st, population pop, and growth 0.
    */
    City(int popRank, string nm, string st, int pop);

    /**
     * Non-Default Constructor
     * Requires: Nothing
     * Modifies: populationRank, name, state, population, growth
     * Effects: Constructs City with populationRank popRank, name nm, state st, population pop, and growth gr.
    */
    City(int popRank, string nm, string st, int pop, double gr);

    /**
     * Destructor
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Do Nothing
    */
    ~City();

    /**
     * PopulationRank Setter
     * Requires: Nothing
     * Modifies: populationRank
     * Effects: Sets populationRank to popRank
    */
    void setPopulationRank(int popRank);

    /**
     * Name Setter
     * Requires: Nothing
     * Modifies: name
     * Effects: sets name to nm
    */
    void setName(string nm);

    /**
     * State Setter
     * Requires: Nothing
     * Modifies: state
     * Effects: sets state to st
    */
    void setState(string st);

    /**
     * Population Setter
     * Requires: Nothing
     * Modifies: population
     * Effects: sets population to pop
    */
    void setPopulation(int pop);

    /**
     * Growth Setter
     * Requires: Nothing
     * Modifies: growth
     * Effects: Sets growth to gr
    */
    void setGrowth(int gr);

    /**
     * Population Getter
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns populationRank
    */
    int getPopulationRank() const;

    /**
     * Name Getter
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns name
    */
    string getName() const;

    /**
     * State Getter
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns state
    */
    string getState() const;

    /**
     * Population Getter
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns population
    */
    int getPopulation() const;

    /**
     * Growth Getter
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns growth
    */
    double getGrowth() const;

    /**
     * Overloaded Operator (binary)
     * Friend of the class (not a member)
     * Requires: nothing
     * Modifies: nothing
     * Effects: Prints the City field values
    */
    friend ostream& operator <<(ostream& outs, const City &city);

    /**
     * Overloaded Operator (binary)
     * Friend of the class (not a member)
     * Requires: nothing
     * Modifies: nothing
     * Effects: Compares City objects
    */
    friend bool operator <(const City &c1, const City &c2);

    /**
     * Overloaded Operator (binary)
     * Friend of the class (not a member)
     * Requires: nothing
     * Modifies: nothing
     * Effects: Compares City objects
    */
    friend bool operator >(const City &c1, const City &c2);

    /**
     * Overloaded Operator (binary)
     * Friend of the class (not a member)
     * Requires: nothing
     * Modifies: nothing
     * Effects: Compares City objects
    */
    friend bool operator <=(const City &c1, const City &c2);

    /**
     * Overloaded Operator (binary)
     * Friend of the class (not a member)
     * Requires: nothing
     * Modifies: nothing
     * Effects: Compares City objects
    */
    friend bool operator >=(const City &c1, const City &c2);

    /**
     * Overloaded Operator (binary)
     * Friend of the class (not a member)
     * Requires: nothing
     * Modifies: nothing
     * Effects: Compares City objects
    */
    friend bool operator ==(const City &c1, const City &c2);
};

#endif //PROJECT_2_CITY_H