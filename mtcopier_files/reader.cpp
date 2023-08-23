/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"

#include "writer.h"

/**
 * implement the functions needed for this class
 **/
std::ifstream reader::in;
pthread_mutex_t readMutex = PTHREAD_MUTEX_INITIALIZER;

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
        pthread_mutex_lock(&readMutex);
        if (getline(in, line)) {
            writer::append(line);
        } else {
            pthread_mutex_unlock(&readMutex);
            break;
        }
        pthread_mutex_unlock(&readMutex);
    }
    return nullptr;
}
