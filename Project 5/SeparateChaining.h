//
// Created by Lisa Dion on 3/28/18.
//

#ifndef CS124B_HASHING_SEPARATECHAINING_H
#define CS124B_HASHING_SEPARATECHAINING_H

#include <functional>
#include <string>
#include <vector>

template<typename T>
class SeparateChaining {
private:
    int tableSize;
    std::vector<std::vector<T>> hashTable;
    std::function<std::string(const T &)> getKey;

    unsigned long hornerHash(const std::string &key) {
        unsigned long hashVal = 0;
        for (char ch : key) {
            hashVal = 37*hashVal + ch;
        }
        return hashVal % tableSize;
    }

public:
    SeparateChaining(int tableSizeIn, std::function<std::string(const T &)> getKeyIn) {;
        if (tableSizeIn <= 0) {
            tableSizeIn = 13;
        }
        tableSize = tableSizeIn;
        hashTable.resize(tableSize);
        // Make sure all hashTable indexes contain empty vectors
        for (std::vector<T> &vec : hashTable) {
            vec.clear();
        }
        getKey = getKeyIn;
    }

    void insert(const T &item, int &numSepChainReads) {
        std::string key = getKey(item);
        T temp;
        // Check if the item is already in the hashTable
        if (!search(key, temp, numSepChainReads)) {
            // Item is not there. Insert it.
            unsigned long index = hornerHash(key);
            hashTable[index].push_back(item); ++numSepChainReads;
        }
        // Item is already in the hashTable. Do nothing.
    }

    // Assuming that every object T has a unique key
    // This will not change the size of the hashTable.
    // Returns false if it finds an empty hashItem. Otherwise, sets the item to empty and returns true.
    bool remove(const std::string &key, int &numSepChainReads) {
        unsigned long index = hornerHash(key);
        // Loop through vector at the index to find the item with the matching key
        for (int i = 0; i < hashTable[index].size(); ++i) {
            ++numSepChainReads; if (getKey(hashTable[index][i]) == key) {
                // We found the object
                // The erase method takes an iterator. The begin method returns an iterator
                // positioned at the first element. Can add indexes from there.
                hashTable[index].erase(hashTable[index].begin() + i); ++numSepChainReads;
                return true;
            }
        }
        // We went through the loop and didn't find the item.
        return false;
    }

    // If the object is not found from the key, return false.
    // Otherwise, set item to the object and return true.
    bool search(const std::string &key, T &item, int &numSepChainReads) {
        unsigned long index = hornerHash(key);
        for (T &hashItem : hashTable[index]) { ++numSepChainReads;
            if (getKey(hashItem) == key) {
                // We found the object
                item = hashItem;
                return true;
            }
        }
        // We went through the loop and didn't find the item.
        return false;
    }
};

#endif //CS124B_HASHING_SEPARATECHAINING_H