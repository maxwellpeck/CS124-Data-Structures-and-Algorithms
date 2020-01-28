`//
// Created by Lisa Dion on 4/2/18.
//

#ifndef CS124B_HASHING_PROBING_H
#define CS124B_HASHING_PROBING_H

#include <functional>
#include <string>
#include <vector>

template<typename T>
class Probing {
private:
    // An enum is a specified data type with a finite number of possible values.
    enum status {empty, active, removed};

    // A struct is a way to group data of different types together.
    // Can use the dot operator to access each data field.
    struct hashItem {
        T item;
        status state;
    };

    int numberOfItems;
    int tableSize;
    std::vector<hashItem> hashTable;
    std::function<std::string(const T &)> getKey;

    unsigned long hornerHash(const std::string &key) {
        unsigned long hashVal = 0;
        for (char ch : key) {
            hashVal = 37*hashVal + ch;
        }
        return hashVal % tableSize;
    }

    int nextPrime(int n) {
        if (n % 2 == 0) {
            ++n;
        }
        bool prime = false;
        while (!prime) {
            prime = true;
            for (int i = 3; i * i <= n; i += 2) {
                if (n % i == 0) {
                    prime = false;
                }
            }
            n += 2;
        }
        return (n-2);
    }

    void rehash(int &numLinProbingReads) {
        // Make a copy of the hash table.
        std::vector<hashItem> oldTable = hashTable;
        // Resize the hash table and empty it.
        hashTable.resize(nextPrime(tableSize * 2));
        for (hashItem &h : hashTable) { ++numLinProbingReads;
            h.state = empty;
        }
        // Update fields.
        tableSize = hashTable.size();
        numberOfItems = 0;
        // Reinsert the active items.
        for (hashItem &h : oldTable) {
            if (h.state == active) {
                insert(h.item, numLinProbingReads);
            }
        }
    }

public:
    Probing(int tableSizeIn, std::function<std::string(const T &)> getKeyIn) {
        if (tableSizeIn <= 0) {
            tableSizeIn = 13;
        }
        tableSize = tableSizeIn;
        hashTable.resize(tableSize);
        for (hashItem &h : hashTable) {
            h.state = empty;
        }
        getKey = getKeyIn;
        numberOfItems = 0;
    }

    void insert(const T &item, int &numLinProbingReads) {
        std::string key = getKey(item);
        // Check that the item is not already in the hash table.
        T temp;
        if (!search(key, temp, numLinProbingReads)) {
            unsigned long index = hornerHash(key);
            // Check status of item at the index in the hash table.
            // TODO: Make sure this cannot be an infinite loop.
            while (hashTable[index].state == active) { ++numLinProbingReads;
                // We need to probe.
                ++index;
                // To make sure the index does not go out of bounds,
                // mod it by the size of the hash table.
                index %= tableSize;
            }
            hashTable[index].item = item;
            hashTable[index].state = active;
            ++numberOfItems;
            if (numberOfItems > (tableSize / 2.0)) {
                rehash(numLinProbingReads);
            }
        }
    }

    // Assuming that every object T has a unique key.
    // This will not change the size of the hashTable.
    // Returns false if it cannot find the hashItem. Otherwise, sets the item to empty and returns true.
    bool remove(const std::string &key, int &numLinProbingReads) {
        unsigned long index = hornerHash(key);
        unsigned long initialIndex = index;
        while (hashTable[index].state != empty) {
            numLinProbingReads += 2; if (hashTable[index].state == active && getKey(hashTable[index].item) == key) {
                // We found the item. Remove it.
                hashTable[index].state = removed;
                --numberOfItems;
                return true;
            }
            // We need to probe.
            ++index;
            // To make sure the index does not go out of bounds,
            // mod it by the size of the hash table.
            index %= tableSize;
            if (index == initialIndex) {
                // We have made a loop through the table and have not found the item.
                return false;
            }
        }
        // Our search failed. We cannot remove the item.
        return false;
    }

    // If the object is not found from the key, return false.
    // Otherwise, set item to the object and return true.
    bool search(const std::string &key, T &item, int &numLinProbingReads) {
        unsigned long index = hornerHash(key);
        unsigned long initialIndex = index;
        while (hashTable[index].state != empty) { ++numLinProbingReads;
            ++numLinProbingReads; if (hashTable[index].state == active && getKey(hashTable[index].item) == key) {
                // We found the item.
                item = hashTable[index].item; ++numLinProbingReads;
                return true;
            }
            // We need to probe.
            ++index;
            // To make sure the index does not go out of bounds,
            // mod it by the size of the hash table.
            index %= tableSize;
            if (index == initialIndex) {
                // We have made a loop through the table and have not found the item.
                return false;
            }
        }
        // Our search failed.
        return false;
    }

    void printTable(std::ostream &outs) const {
        for (int index = 0; index < tableSize; ++index) {
            outs << index << ": ";
            if (hashTable[index].state == active) {
                // This assumes that the << operator is overloaded for the item to print
                outs << hashTable[index].item;
            }
            outs << std::endl;
        }
    }

    int getTableSize() const {
        return tableSize;
    }
};

#endif //CS124B_HASHING_PROBING_H
