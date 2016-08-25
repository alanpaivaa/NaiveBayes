//
// Created by Alan Jeferson on 24/08/16.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "defines.h"


/**
 * @brief Loads the values from a CSV file into the training and data sets according to the
 * training ratio.
 * */
void loadCsv() {

    int c; /* Last read character */
    char buffer[10]; /* Holds the current character in the file */
    char bc = 0; /* Counter for the buffer, for appending new characters each time */
    char path[100] = DATASET_DIR;
    FILE *file; /* File pointer */

    int count = COLUMNS; /* Tells the position of a character in a line */
    int trainingCount = -1; /* Line count for the training set */
    int testCount = -1; /* Line count for the test set */
    int selectedSet; /* 0 for training, 1 for test */
    int randomNumber;

    // Opening the file
    strcat(path, "/");
    strcat(path, DATASET);
    strcat(path, ".csv");
    file = fopen(path, "r");
    if(file == NULL) {
        printf("Could not open file\n");
        return;
    }

    /* While there's file to read */
    while((c = fgetc(file)) != EOF) {

        if(c == COMMA_ASCII || c == LINE_FEED_ASCII) { /*A new value is ready to go */

            buffer[bc] = '\0';

            /* New Line */
            if(count == COLUMNS) {

                count = 0;

                /* Choosing the proper set */
                if(RANDOM_SETS && (trainingCount + 1) < TRAINING_LINES && (testCount + 1) < TEST_LINES) {
                    randomNumber = rand()%100;
                    selectedSet = randomNumber%2;
                } else if((trainingCount + 1) < TRAINING_LINES) { /* First training set */
                    selectedSet = 0;
                } else { /* Then test set */
                    selectedSet = 1;
                }

                // Increment the line count for the sets */
                if(selectedSet) {
                    testCount++;
                } else {
                    trainingCount++;
                }

            }

            /* Test set */
            if(selectedSet) {
                *(&(testSet[0][0]) + ((testCount * COLUMNS) + count)) = atof(buffer);
            } else { /* Training set */
                *(&(trainingSet[0][0]) + ((trainingCount * COLUMNS) + count)) = atof(buffer);
            }

            count++;
            bc = 0;

        } else {
            buffer[bc++] = c;
        }
    }

    // Making sure that the last character is read
    if(bc > 0) {
        buffer[bc] = '\0';
        if(selectedSet) {
            *(&(testSet[0][0]) + ((testCount * COLUMNS) + count)) = atof(buffer);
        } else { // Training set
            *(&(trainingSet[0][0]) + ((trainingCount * COLUMNS) + count)) = atof(buffer);
        }
    }

    // Close the file
    fclose(file);
}

void writeCsv() {

    FILE *fileMeans, *fileStdevs; // Pointers to the files
    int i, j; // Control variables
    char path[30] = SUMMARIES_DIR; // General path
    char pathMeans[30], pathStdev[30]; // Specific paths to the means and stdevs files

    // Opening the file
    strcat(path, "/");
    strcat(path, DATASET);
    strcpy(pathMeans, path);
    strcat(pathMeans, SUMMARIES_SUFIX_MEANS);
    strcpy(pathStdev, path);
    strcat(pathStdev, SUMMARIES_SUFIX_STDEVS);
    fileMeans = fopen(pathMeans, "w");
    fileStdevs = fopen(pathStdev, "w");

    // Checking if the file opened correctly
    if(fileMeans == NULL || fileStdevs == NULL) {
        printf("Could not open the file :(\n");
        return;
    }

    // Writing the file
    for(i = 0; i < CLASSES; i++) {
        for(j = 0; j < COLUMNS - 1; j++) {
            printf("%f ", means[i][j]);
            fprintf(fileMeans, "%f", means[i][j]);
            fprintf(fileStdevs, "%f", stdevs[i][j]);
            if(i != CLASSES - 1 || j != COLUMNS - 2) {
                fprintf(fileMeans, ",");
                fprintf(fileStdevs, ",");
            }
            if(j == COLUMNS - 2 && i < CLASSES - 1) {
                fprintf(fileMeans, "\n");
                fprintf(fileStdevs, "\n");
            }
        }
    }

    // Closing files
    fclose(fileMeans);
    fclose(fileStdevs);

    printf("File written successfully!");

}