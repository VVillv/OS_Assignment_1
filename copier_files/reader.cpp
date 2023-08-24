/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"
#include <functional>
#include <ctime>  // Include the ctime header

reader::reader(const std::string& name, writer& mywriter): thewriter(mywriter) {
    in.open(name);
    if (!in.is_open()) {
        std::cerr << "Failed to open the input file: " << name << std::endl;
        exit(EXIT_FAILURE);
    }
}

void reader::run() {
    std::string line;

    clock_t startTime = clock();  // Capture the start time

    while (std::getline(in, line)) {
        thewriter.append(line);
    }

    clock_t endTime = clock();  // Capture the end time

    double readTime = (endTime - startTime) / (double)CLOCKS_PER_SEC;  // Calculate reading duration

    std::cout << "Time taken to read: " << readTime << " seconds." << std::endl;  // Print reading duration
    
    in.close();
}
