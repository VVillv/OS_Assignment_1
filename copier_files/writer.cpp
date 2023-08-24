/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/

#include "writer.h"
#include <ctime>  // Include the ctime header

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
    clock_t startTime = clock();  // Capture the start time

    while (!queue.empty()) {
        out << queue.front() << std::endl;
        queue.pop_front();
    }

    clock_t endTime = clock();  // Capture the end time

    double writeTime = (endTime - startTime) / (double)CLOCKS_PER_SEC;  // Calculate writing duration

    std::cout << "Time taken to write: " << writeTime << " seconds." << std::endl;  // Print writing duration

    out.close();
}

void writer::append(const std::string& line) {
    queue.push_back(line);
}
