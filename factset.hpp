#ifndef FACTSET_H
#define FACTSET_H

#include <map>
#include <iostream>

enum class DataState {
    NOT_SECRET,
    SECRET,

    NONE,
};

class Factset {
public:
    Factset(){};

    DataState getFact(std::string name);
    void updateSet(std::string name, DataState state);
    void mergeSets(Factset setToMerge);
private:
    std::map<std::string, DataState> mFacts;

};

#endif