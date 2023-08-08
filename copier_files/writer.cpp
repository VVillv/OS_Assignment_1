/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/

#include "writer.h"

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
    while (!queue.empty()) {
        out << queue.front() << std::endl;
        queue.pop_front();
    }
    out.close();
}

void writer::append(const std::string& line) {
    queue.push_back(line);
}
