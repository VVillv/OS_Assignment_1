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
pthread_cond_t writerCond = PTHREAD_COND_INITIALIZER;

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
        pthread_mutex_lock(&writerMutex);

        // Wait until there's a line to write
        while (queue.empty()) {
            pthread_cond_wait(&writerCond, &writerMutex);
        }

        out << queue.front() << std::endl;
        queue.pop_front();

        pthread_mutex_unlock(&writerMutex);
        pthread_cond_signal(&writerCond); // Signal other threads
    }
    return nullptr;
}

void writer::append(const std::string& line) {
    pthread_mutex_lock(&writerMutex); // Lock the mutex to safely push to the queue
    queue.push_back(line);
    pthread_mutex_unlock(&writerMutex); // Unlock the mutex after pushing to the queue
    pthread_cond_signal(&writerCond); // Signal the runner thread that there's a new line to write
}

void writer::setfinished() {}
