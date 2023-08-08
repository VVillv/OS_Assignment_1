/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"
#include "writer.h"
#include <cstdlib>
/**
 * these need to be global variables as you'll need handle cleaning them up in
 *cleanup which will automatically be called on program exit
 **/
reader* readers;
writer* writers;

void cleanup() {
    /**
     * perform any cleanup you need to do here for global pointers
     **/
    delete readers;
    delete writers;
}

int main(int argc, char** argv) {
    atexit(cleanup);
    /**
     * check command line arguments
     **/
    if (argc != 3) {
        std::cer << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
    }
    /**
     * process command line arguments
     **/
    std::string infile = argv[1];
    std::string outfile = argv[2];
    /**
     * initiliaze the reader and writer classes
     **/
    writer::init(outfile);
    reader::init(infile);
    /**
     * initialize the running of each thread. Note you just call run() on each
     * object here, you'll call pthread_create itself in the run function.
     **/
    readers->run();
    writers->run();
    /**
     *
     * have loop here waiting for the threads to bomplete. Please see
     * section on avoiding busy waiting on the assignment specification to see
     * what need to be done here
      **/
    return EXIT_SUCCESS;
}
