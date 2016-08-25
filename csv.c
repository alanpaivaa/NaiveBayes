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

/**
 * @brief Writes the given summary array to a file.
 * */
void writeSummaryToFile(float *vector, FILE *file) {

    int i;

    for(i = 0; i < CLASSES * (COLUMNS - 1); i++) {
        fprintf(file, "%f", *(vector + i));
        if((i % (COLUMNS - 1)) < COLUMNS - 2) {
            fprintf(file, ",");
        }
        if((i % (COLUMNS - 1)) == COLUMNS - 2) {
            fprintf(file, "\n");
        }
    }

}

/**
 * @brief Writes both stdev and means matrixes to a file.
 * */
void writeSummariesCsv() {

    FILE *file; // Pointers to the files
    char path[30] = SUMMARIES_DIR; // Path to file

    // Opening the file
    strcat(path, "/");
    strcat(path, DATASET);
    strcat(path, ".csv");
    file = fopen(path, "w");

    // Checking if the file opened correctly
    if(file == NULL) {
        printf("Could not open the file :(\n");
        return;
    }

    // Writing the file
    writeSummaryToFile(&means[0][0], file);
    writeSummaryToFile(&stdevs[0][0], file);

    // Closing files
    fclose(file);

}

/**
 * @brief Loads a CSV file into the summaries (means and stdevs) arrays.
 * */
void loadSummariesFromCsv() {

    FILE *file; // Pointers to the files
    char path[30] = SUMMARIES_DIR; // Path to file
    int c; /* Last read character */
    char buffer[10]; /* Holds the current character in the file */
    char bc = 0; /* Counter for the buffer, for appending new characters each time */
    int count = 0; /* Number of characters found */
    int offset = CLASSES * (COLUMNS - 1);

    // Opening the file
    strcat(path, "/");
    strcat(path, DATASET);
    strcat(path, ".csv");
    file = fopen(path, "r");

    while((c = fgetc(file)) != EOF) {
        if(c == COMMA_ASCII || c == LINE_FEED_ASCII) { /*A new value is ready to go */

            buffer[bc] = '\0';
            bc = 0;

            // Choosing the proper array
            if(count < offset) {
                *(&means[0][0] + count) = atof(buffer);
            } else {
                *(&stdevs[0][0] + (count - offset)) = atof(buffer);
            }

            count++;

        } else {
            buffer[bc++] = c;
        }
    }

    fclose(file);

}