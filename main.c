//
// Created by Alan Jeferson on 21/08/16.
//
#include<stdio.h>
#include<stdlib.h>

#define FILE_PATH "datasets/pima.csv"
#define COMMA_ASCII 44
#define LINE_FEED_ASCII 10

typedef struct {
    int lines;
    int rows;
    float *vector;
} Dataset;

Dataset* buildDataset(int lines, int rows) {
    Dataset *dataset = (Dataset *) malloc(sizeof(dataset));
    dataset->lines = lines;
    dataset->rows = rows;
    dataset->vector = (float *) malloc(dataset->lines * dataset->rows * sizeof(float));
    return dataset;
}

void printDataset(Dataset *dataset) {
    int i, j;
    for (i = 0; i < dataset->lines; i++) {
        for (j = 0; j < dataset->rows; j++) {
            printf("%f", *(dataset->vector + ((i * dataset->rows) + j)));
            if(j < dataset->rows - 1) {
                printf(", ");
            }
        }
        printf("\n");
    }
}

void loadCsvInto(Dataset *dataset) {

    FILE *file = fopen(FILE_PATH, "r");

    if(file == NULL) {
        printf("Could not open file\n");
        return;
    }

    int c;
    char buffer[10];
    char bc = 0;
    int dc = 0;
    while((c = fgetc(file)) != EOF) {
        if(c == COMMA_ASCII || c == LINE_FEED_ASCII) {
            buffer[bc] = '\0';
            *(dataset->vector + dc) = atof(buffer);
            dc++;
            bc = 0;
        } else {
            buffer[bc++] = c;
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {

    Dataset *dataset = buildDataset(768, 9);
    loadCsvInto(dataset);
    printDataset(dataset);

    return 0;
}