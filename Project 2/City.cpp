//
// Created by Maxwell Peck on 2/13/18.
//

#include "City.h"

City::City() {
    populationRank = 0;
    name = "Name";
    state = "State";
    population = 0;
    growth = 0.0;
}

City::City(int popRank) {
    populationRank = popRank;
    name = "Name";
    state = "State";
    population = 0;
    growth = 0.0;
}

City::City(int popRank, string nm) {
    populationRank = popRank;
    name = nm;
    state = "State";
    population = 0;
    growth = 0.0;
}

City::City(int popRank, string nm, string st) {
    populationRank = popRank;
    name = nm;
    state = st;
    population = 0;
    growth = 0.0;
}

City::City(int popRank, string nm, string st, int pop) {
    populationRank = popRank;
    name = nm;
    state = st;
    population = pop;
    growth = 0.0;
}

City::City(int popRank, string nm, string st, int pop, double gr) {
    populationRank = popRank;
    name = nm;
    state = st;
    population = pop;
    growth = gr;
}

City::~City() {
    //Emptiness like a black hole
}

void City::setPopulationRank(int popRank) {
    populationRank = popRank;
}

void City::setName(string nm) {
    name = nm;
}

void City::setState(string st) {
    state = st;
}

void City::setPopulation(int pop) {
    population = pop;
}

void City::setGrowth(int gr) {
    growth = gr;
}

int City::getPopulationRank() const {
    return populationRank;
}

string City::getName() const {
    return name;
}

string City::getState() const {
    return state;
}

int City::getPopulation() const {
    return population;
}

double City::getGrowth() const {
    return growth;
}

ostream& operator << (ostream& outs, const City& city) {
    outs << setfill('.') << setw(10) << left << city.populationRank << setw(30) << left << city.name << setw(25) << left << city.state <<
         setw(15) << left << city.population << setw(16) << right << city.growth << '%';
    return outs;
}