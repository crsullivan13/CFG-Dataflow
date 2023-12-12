#include "bbl.hpp"

Bbl::~Bbl() {
    for ( auto instr : mInstructions ) {
        delete instr;
    }
}