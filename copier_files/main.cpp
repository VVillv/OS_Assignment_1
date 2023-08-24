/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"
#include "writer.h"
#include <cstdlib>
#include <iostream>
#include <ctime>  // Include the ctime header

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

    clock_t startTime = clock();  // Capture the start time

    myReader.run();
    myWriter.run();

    clock_t endTime = clock();  // Capture the end time

    double totalTime = (endTime - startTime) / (double)CLOCKS_PER_SEC;  // Calculate total duration

    std::cout << "Total time taken: " << totalTime << " seconds." << std::endl;  // Print total duration
    
    return EXIT_SUCCESS;
}
