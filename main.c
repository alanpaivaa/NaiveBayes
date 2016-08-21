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
#define PIMA_COLUMNS 9
#define PIMA_CLASS 2

// Dataset corrente
const  int lines = PIMA_LINES;
const int rows = PIMA_COLUMNS;
char *path = PIMA_PATH;
float dataset[PIMA_LINES][PIMA_COLUMNS];
float means[PIMA_CLASS][PIMA_COLUMNS-1];
float stdevs[PIMA_CLASS][PIMA_COLUMNS-1];

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
    for(i = 0; i<(int)(PIMA_LINES*0.7)+1; i++)
    {
        //iff the data is from the correct class and it's part of the training set add it to the mean calculation
        if(dataset[i][PIMA_COLUMNS-1]==classNumber)
        {
            values+=dataset[i][columnNumber];
            total++;
        }

    }

    return values/(float)(total);

}

void calculateSummaries()
{
    int i,j;
    for(j = 0; j<PIMA_CLASS;j++)
    {
        for(i = 0; i<PIMA_COLUMNS-1;i++)
        {
            means[j][i] = calculateMean(j,i);
        
        }
        //stdevs[j] = summaryStdv(j);
    }
}


void printMeans()
{
    int i, j ;
    for(i = 0; i<PIMA_CLASS;i++ )
    {
        for(j = 0; j<PIMA_COLUMNS-1;j++)
        {
            printf("%f\n",means[i][j] );
        }
    }
}
int main(int argc, char *argv[]) {

    // Configurações de dataset;
    loadCsv();
    calculateSummaries();
    //printDataset();
    printMeans();

    return 0;
}