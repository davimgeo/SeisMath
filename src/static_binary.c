#include <stdio.h>
#include <stdlib.h>
#include "../include/static_binary.h"

#define BINARY_WRITE "wb"
#define BINARY_READ "rb"

void write2D(const char* FILE_PATH, float* arr, size_t type, int row, int column) 
{
    FILE* bin_data = fopen(FILE_PATH, BINARY_WRITE); 
    if (bin_data == NULL) 
    {
        printf("Could not open the file.\n");
        exit(-1);
    }

    fwrite(arr, type, row * column, bin_data); 

    fclose(bin_data);   
}

void read2D(const char* FILE_PATH, float* arr, size_t type, int row, int column)
{
    FILE* bin_data = fopen(FILE_PATH, BINARY_READ);
    if (bin_data == NULL) 
    {
        printf("Could not open the file.\n");
        exit(-1);
    }

    fread(arr, type, row * column, bin_data); 

    fclose(bin_data);  
}

void write1D(const char* FILE_PATH, float* arr, size_t type, int size) 
{
    FILE* bin_data = fopen(FILE_PATH, BINARY_WRITE); 
    if (bin_data == NULL) 
    {
        printf("Could not open the file for writing!\n");
        exit(-1);
    }

    // Escrevendo o array 1D no arquivo
    fwrite(arr, type, size, bin_data);  

    fclose(bin_data);   
}

void read1D(const char* FILE_PATH, float* arr, size_t type, int size) 
{
    FILE* bin_data = fopen(FILE_PATH, BINARY_READ);
    if (bin_data == NULL) 
    {
        printf("Could not open the file for reading!\n");
        exit(-1);
    }

    fread(arr, type, size, bin_data); 
    fclose(bin_data);  
}

