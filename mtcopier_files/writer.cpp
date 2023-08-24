/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "writer.h"
#include "reader.h"
#include <pthread.h>

std::ofstream writer::out;
std::deque<std::string> writer::queue;
pthread_mutex_t writer::writerMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t writer::writerCond = PTHREAD_COND_INITIALIZER;

/**
 * implement these functions requred for the writer class
 **/
void writer::init(const std::string& name) {
    out.open(name);
    if (!out.is_open()) {
        std::cerr << "Failed to open the output file: " << name << std::endl;
        exit(EXIT_FAILURE);
    }
}

void writer::run() {
    pthread_t thread;
    pthread_create(&thread, nullptr, runner, nullptr);
    pthread_join(thread, nullptr);
}

void* writer::runner(void* arg) {
    while (true) {
        pthread_mutex_lock(&writerMutex); // Lock the mutex to safely access the queue
        if (!queue.empty()) {
            out << queue.front() << std::endl;
            queue.pop_front();
        } else {
            pthread_mutex_unlock(&writerMutex); // Unlock the mutex before breaking out of the loop
            break;
        }
        pthread_mutex_unlock(&writerMutex); // Unlock the mutex after processing a line
    }
    return nullptr; 
}

void writer::append(const std::string& line) {
    pthread_mutex_lock(&writerMutex); // Lock the mutex to safely push to the queue
    queue.push_back(line);
    pthread_cond_signal(&writerCond); // Signal the writer thread
    pthread_mutex_unlock(&writerMutex); // Unlock the mutex after pushing to the queue
}

void writer::setfinished() {
}
