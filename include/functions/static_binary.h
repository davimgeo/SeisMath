#ifndef BIN_FILE_H
#define BIN_FILE_H

#include <stdio.h>

void write2D(const char* FILE_PATH, float* arr, size_t type, int row, int column);

void read2D(const char* FILE_PATH, float* arr, size_t type, int row, int column);

void write1D(const char* FILE_PATH, float* arr, size_t type, int size);

void read1D(const char* FILE_PATH, float* arr, size_t type, int size);

#endif // !BIN_FILE_H
