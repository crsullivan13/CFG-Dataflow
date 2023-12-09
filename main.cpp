#include <algorithm>
#include <fstream>
#include <iostream>
#include <sys/stat.h>

bool optionExsits(char** begin, char** end, std::string option) {
    return std::find(begin, end, option) != end;
}

const char* getOptionInput(char** begin, char** end, std::string option) {
    char** itr = std::find(begin, end, option);
    const char* input = "\0";

    //Some prepend sorcery
    if ( itr != end && ++itr != end ) {
        input = *itr;
    }

    return input;
}

int main(int argc, char** argv) {
    if ( argc > 1 ) {
        if ( optionExsits(argv, argv + argc, "-h") ) {
            std::cout << "Get some help\n";
            std::cout << "Expecting \"./analysis -i <infile.ll> -g <outdir>\" for CFG Inference\n";
            std::cout << "Expecting \"./analysis -i <infile.ll> -s\" for Static Dataflow\n";
        } else {
            bool optionsFail = false;

            const char* infile = getOptionInput(argv, argv + argc, "-i"); //Input file

            bool shouldOutputGraph = false; //We should only output graphs if the -g option exists

            if ( *infile == '\0' ) {
                std::cout << "No infile given\n";
                optionsFail = true;
            } else if ( optionExsits(argv, argv + argc, "-g") ) { //Output dir
                shouldOutputGraph = true;

                const char* outdir = getOptionInput(argv, argv + argc, "-g");

                if ( *outdir == '\0' ) {
                    std::cout << "No outdir given, defaulting to \"out\"\n";
                    mkdir("out", 0777);
                } else {
                    mkdir(outdir, 0777);
                }
            }

            bool shouldDoDataflow = optionExsits(argv, argv + argc, "-s"); //Switch for data flow anaylysis

            if ( !optionsFail ) {
                //Call analysis function, pass in in file/out dir/booleans
            } else {
                std::cout << "Bad command line inputs, use -h option for help\n";
            }
        }
    } else {
        std::cout << "Not enough arguments, use -h for help\n";
    }

    return 0;
}