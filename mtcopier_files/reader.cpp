/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"
#include <ctime> 
#include "writer.h"

/**
 * implement the functions needed for this class
 **/
std::ifstream reader::in;
pthread_mutex_t reader::readMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t reader::readCond = PTHREAD_COND_INITIALIZER;


void reader::init(const std::string& name) {
    in.open(name);
    if (!in.is_open()) {
        std::cerr << "Failed to open the input file: " << name << std::endl;
        exit(EXIT_FAILURE);
    }
}

void reader::run() {
    pthread_t thread;
    pthread_create(&thread, nullptr, runner, nullptr);
    pthread_join(thread, nullptr);
}

void* reader::runner(void* arg) {
    std::string line;
    while (true) {
        clock_t start = clock(); // Start the clock
        pthread_mutex_lock(&readMutex);
        
        // Wait until there's a line to read
        while (!getline(in, line)) {
            pthread_cond_wait(&readCond, &readMutex);
        }

        clock_t end = clock(); // Stop the clock
        clock_t duration = end - start;
        double time_taken = ((double)duration) / CLOCKS_PER_SEC; // Convert to seconds

        std::cout << "Time taken to read a line: " << time_taken << " seconds." << std::endl;

        if (!getline(in, line)) {
            pthread_mutex_unlock(&readMutex);
            break;
        }

        if (!line.empty()) {
            writer::append(line);
        } else {
            pthread_mutex_unlock(&readMutex);
            break;
        }
        
        pthread_mutex_unlock(&readMutex);
    }
    return nullptr;
}
