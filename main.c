//
// Created by Alan Jeferson on 21/08/16.
//
#include<stdio.h>
#include<stdlib.h>

#define COMMA_ASCII 44
#define LINE_FEED_ASCII 10

// Dataset Pima
#define PIMA_PATH "datasets/pima.csv"
#define PIMA_LINES 768
#define PIMA_ROWS 9

// Dataset corrente
const  int lines = PIMA_LINES;
const int rows = PIMA_ROWS;
char *path = PIMA_PATH;
float dataset[lines][rows];

void printDataset() {
    int i, j;
    for (i = 0; i < lines; i++) {
        for (j = 0; j < rows; j++) {
            printf("%f", dataset[i][j]);
            if(j < rows - 1) {
                printf(", ");
            }
        }
        printf("\n");
    }
}

void loadCsv() {

    FILE *file = fopen(path, "r");

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
            *(&(dataset[0][0]) + dc) = atof(buffer);
            dc++;
            bc = 0;
        } else {
            buffer[bc++] = c;
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {

    // Configurações de dataset;
    loadCsv();
    printDataset();

    return 0;
}