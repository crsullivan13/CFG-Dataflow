#include <algorithm>
#include <fstream>
#include <iostream>
#include <sys/stat.h>

bool optionExsits(char** begin, char** end, std::string option) {
    return std::find(begin, end, option) != end;
}

char* getOptionInput(char** begin, char** end, std::string option) {
    char** itr = std::find(begin, end, option);
    char* input;

    if ( itr != end && ++itr != end ) {
        input = *itr;
    }

    return input;
}

int main(int argc, char** argv) {
    
    if ( optionExsits(argv, argv + argc, "-h") ) {
        std::cout << "Get some help\n";
        std::cout << "Expecting \"./analysis -i <infile.ll> -g <outdir>\" for CFG Inference\n";
        std::cout << "Expecting \"./analysis -i <infile.ll> -s\" for Static Dataflow\n";
    } else {
        bool optionsFail = false;

        char* infile = getOptionInput(argv, argv + argc, "-i");

        if ( *infile == '\0' ) {
            std::cout << "No infile given\n";
            optionsFail = true;
        }

        if ( optionExsits(argv, argv + argc, "-g") ) {
            char* outdir = getOptionInput(argv, argv + argc, "-g");

            if ( *outdir == '\0' ) {
                std::cout << "No outdir given, defaulting to \"out\"\n";
                mkdir("out", 0777);
            } else {
                mkdir(outdir, 0777);
            }
        }

        bool shouldDoDataflow = optionExsits(argv, argv + argc, "-s");

        if ( !optionsFail ) {
            //call CFG inference

            if ( shouldDoDataflow ) {
                //call data flow analysis
            }

        } else {
            std::cout << "Bad command line inputs, use -h option for help\n";
        }

    }

    return 0;
}