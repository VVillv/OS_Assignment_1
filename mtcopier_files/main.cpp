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
    delete[] readers;
    delete[] writers;
}

int main(int argc, char** argv) {
    atexit(cleanup);
    /**
     * check command line arguments
     **/
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <num_threads> <input_file> <output_file>" << std::endl;
        return EXIT_FAILURE;
    }
    /**
     * process command line arguments
     **/
    int num_threads = std::stoi(argv[1]);
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
    readers = new reader[num_threads];
    writers = new writer[num_threads];
    /**
     *
     * have loop here waiting for the threads to bomplete. Please see
     * section on avoiding busy waiting on the assignment specification to see
     * what need to be done here
      **/
    for (int i = 0; i < num_threads; ++i) {
    readers[i].run();
    writers[i].run();
    }
    return EXIT_SUCCESS;
}
