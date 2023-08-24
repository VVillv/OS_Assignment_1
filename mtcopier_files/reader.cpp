/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"
#include "writer.h"
#include <ctime>  // Include the <ctime> header for clock()

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
    clock_t startLock, endLock, startRead, endRead;
    std::string line;
    while (true) {
        startLock = clock();  // Start timing for acquiring the lock
        pthread_mutex_lock(&readMutex);
        endLock = clock();  // End timing for acquiring the lock

        startRead = clock();  // Start timing for reading
        if (!getline(in, line)) {
            pthread_mutex_unlock(&readMutex);
            break;
        }
        endRead = clock();  // End timing for reading

        if (!line.empty()) {
            writer::append(line);
        } else {
            pthread_mutex_unlock(&readMutex);
            break;
        }
        
        pthread_mutex_unlock(&readMutex);
    }

    // Convert clock cycles to seconds and print the timings
    double lockTime = (endLock - startLock) / (double)CLOCKS_PER_SEC;
    double readTime = (endRead - startRead) / (double)CLOCKS_PER_SEC;

    std::cout << "Time taken to acquire the lock: " << lockTime << " seconds." << std::endl;
    std::cout << "Time taken to read a line: " << readTime << " seconds." << std::endl;

    return nullptr;
}
