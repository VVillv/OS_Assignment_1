/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"
#include <functional>
#include <ctime>

reader::reader(const std::string& name, writer& mywriter): thewriter(mywriter) {
    in.open(name);
    if (!in.is_open()) {
        std::cerr << "Failed to open the input file: " << name << std::endl;
        exit(EXIT_FAILURE);
    }
}

void reader::run() {
    std::string line;
    clock_t start = clock(); // Start the clock for the entire reading and appending process
    while (std::getline(in, line)) {
        thewriter.append(line);
    }
    clock_t end = clock(); // Stop the clock for the entire process
    clock_t duration = end - start;
    double time_taken = ((double)duration) / CLOCKS_PER_SEC; // Convert to seconds

    std::cout << "Time taken to read and append all lines: " << time_taken << " seconds." << std::endl;

    in.close();
}
