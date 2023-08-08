/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "writer.h"

#include "reader.h"

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
        if (!queue.empty()) {
            out << queue.front() << std::endl;
            queue.pop_front();
        } else {
            break;
        }
    }
    return nullptr; 
}

void writer::append(const std::string& line) {
    queue.push_back(line);
}

void writer::setfinished() {}
