#include "factset.hpp"

DataState Factset::getFact(std::string name) {
    if ( mFacts.find(name) != mFacts.end() ) {
        return mFacts[name];
    } else {
        return DataState::NONE;
    }
}

void Factset::updateSet(std::string name, DataState state) {
    DataState temp = getFact(name);

    if ( temp == DataState::NONE ) {
        mFacts.insert({name, state});
    } else if ( temp < state ) {
        mFacts[name] = state;
    }
}

void Factset::mergeSets(Factset setToMerge) {
    for ( auto& fact : setToMerge.mFacts ) {
        this->updateSet(fact.first, fact.second);
    }
}