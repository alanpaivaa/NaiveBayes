//
// Created by Alan Jeferson on 21/08/16.
//
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define COMMA_ASCII 44
#define LINE_FEED_ASCII 10

// Dataset Pima
#define PIMA_PATH "datasets/pima.csv"
#define PIMA_LINES 768
#define PIMA_COLUMNS 9
#define PIMA_CLASSES 2

// Dataset corrente
const  int lines = PIMA_LINES;
const int rows = PIMA_COLUMNS;
const char *path = PIMA_PATH;
const int classes = PIMA_CLASSES;


float dataset[lines][rows];
float means[classes][rows-1];
float stdevs[classes][rows-1];

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

float calculateMean(int classNumber, int columnNumber)
{
    int i;
    int total = 0;
    float values = 0;
    for(i = 0; i<(int)(lines*0.7)+1; i++)
    {
        //iff the data is from the correct class and it's part of the training set add it to the mean calculation
        if(dataset[i][rows-1]==classNumber)
        {
            values+=dataset[i][columnNumber];
            total++;
        }

    }

    return values/(float)(total);

}

float calculateStdev(int classNumber, int columnNumber, float mean) {

    int i;
    float variance = 0;
    float count = 0;

    for(i = 0; i < (int) (lines*0.7) + 1; i++) {
        if(dataset[i][rows - 1] == classNumber) {
            variance += pow(dataset[i][columnNumber] - mean, 2);
            count += 1;
        }
    }

    return sqrt(variance/count);

}

void calculateSummaries()
{
    int i,j;
    for(i = 0; i<classes;i++) // Iterando sobre classes
    {
        for(j = 0; j<rows-1;j++) // Iterando sobre atributos
        {
            means[i][j] = calculateMean(i, j);
            stdevs[i][j] = calculateStdev(i, j, means[i][j]);
        }

    }
}

void printMeans()
{
    int i, j ;
    for(i = 0; i<classes;i++ )
    {
        for(j = 0; j<rows-1;j++)
        {
            printf("%f\n",means[i][j] );
        }
    }
}

void printStdevs() {

    int i, j;
    for(i = 0; i < classes; i++) {
        for(j = 0; j < rows - 1; j++) {
            printf("%f\n", stdevs[i][j]);
        }
    }

}

void printSummaries() {

    int i, j;
    for (i = 0; i < classes; i++) {
        printf("Classe %d:\n", i);
        for (j = 0; j < rows - 1; j++) {
            printf("(%f, %f)\n", means[i][j], stdevs[i][j]);
        }
        printf("\n");
    }

}

int main(int argc, char *argv[]) {

    // Configurações de dataset;
    loadCsv();
    calculateSummaries();
    //printDataset();
//    printMeans();
//    printStdevs();

    printSummaries();
    return 0;
}