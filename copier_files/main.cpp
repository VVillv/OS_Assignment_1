/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"
#include "writer.h"
#include <cstdlib>
#include <iostream>
/* global variables if needed go here */
int main(int argc, char** argv) {
    /* check command line arguments */
    /* load the file and copy it to the destination */
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string infile = argv[1];
    std::string outfile = argv[2];

    writer myWriter(outfile);
    reader myReader(infile, myWriter);

    myReader.run();
    myWriter.run();
    return EXIT_SUCCESS;
}
