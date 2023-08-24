/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/

#include "writer.h"
#include <ctime>

/**
 * provide your implementation for the writer functions here
 **/
writer::writer(const std::string& name) {
    out.open(name);
    if (!out.is_open()) {
        std::cerr << "Failed to open the output file: " << name << std::endl;
        exit(EXIT_FAILURE);
    }
}

void writer::run() {
    clock_t start = clock(); // Start the clock for the entire writing process

    while (!queue.empty()) {
        out << queue.front() << std::endl;
        queue.pop_front();
    }
    
    clock_t end = clock(); // Stop the clock for the entire process
    clock_t duration = end - start;
    double time_taken = ((double)duration) / CLOCKS_PER_SEC; // Convert to seconds

    std::cout << "Time taken to write all lines: " << time_taken << " seconds." << std::endl;

    out.close();
}

void writer::append(const std::string& line) {
    queue.push_back(line);
}
