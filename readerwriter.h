#ifndef READERWRITER_H
#define READERWRITER_H

#include <semaphore.h>

void reading_writing();
void read_lock();
void read_unlock();
void write_lock();
void write_unlock();
void lock_init();
void lock_destroy();

#endif // READERWRITER_H