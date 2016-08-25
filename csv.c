/**
  ******************************************************************************
  * @file    csv.c
  * @author  Alan Jeferson and Levi Moreira
  * @version V1.1.0
  * @date    25-August-2016
  * @brief   This file contains functions related to work on a test data set.
  * @note    To run the functions on this file you first provide a training data set
  * to calculate the means and the standard deviations. Then you come back to this file
  * to get the predicions, recall and precision runnning properly.
  ******************************************************************************
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "defines.h"


/**
 * @brief Loads the values from a CSV file into the training and data sets according to the
 * training ratio.
 * */
void loadFullDatasetFromCsv() {

    int c; /* Last read character */
    char buffer[15]; /* Holds the current character in the file */
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
 * @brief Loads the test dataset from a CSV file.
 *
 * Loads a CSV file located in test/DATASET, parses its values and saves them
 * into the testset matrix.
 * @see testset
 * */
void loadTestsetFromCsv() {

    int c; /* Last read character */
    char buffer[15]; /* Holds the current character in the file */
    char bc = 0; /* Counter for the buffer, for appending new characters each time */
    char path[30] = TESTSET_DIR;
    FILE *file; /* File pointer */
    int count = 0; /* Tells the position of a character in a line */

    // Opening the file
    strcat(path, "/");
    strcat(path, DATASET);
    strcat(path, ".csv");
    file = fopen(path, "r");
    if(file == NULL) {
        printf("Could not open file %s\n", path);
        return;
    }

    /* While there's file to read */
    while((c = fgetc(file)) != EOF) {

        if(c == COMMA_ASCII || c == LINE_FEED_ASCII) { /*A new value is ready to go */

            buffer[bc] = '\0';

            *(&testSet[0][0] + count) = atof(buffer);

            count++;
            bc = 0;

        } else {
            buffer[bc++] = c;
        }
    }

    // Close the file
    fclose(file);

}

/**
 * @brief Writes the given summary array to a file.
 *
 * Writes the given matrix to a file.
 * @param lines - The number of lines of the matrix.
 * @param columns - The number of columns of the matrix.
 * @param vector - A pointer to the begin of the matrix.
 * @param file - A pointer to the file in which the matrix will be written.
 * */
void writeMatrixToFile(float *vector, FILE *file, int lines, int columns) {

    int i;

    for(i = 0; i < lines * columns; i++) {
        fprintf(file, "%f", *(vector + i));
        if((i % columns) < columns - 1) {
            fprintf(file, ",");
        }
        else {
            fprintf(file, "\n");
        }
    }

}

/**
 * @brief Writes the testset to a csv file.
 *
 * Iterates over the testset matrix and saves each value to a CSV file located in
 * test/DATASET.csv where DATASET refers to the current dataset name.
 * */
void writeTestsetToCsv() {

    FILE *file; // Pointer to the files
    char path[30] = TESTSET_DIR; // Path to file

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

    writeMatrixToFile(&testSet[0][0], file, TEST_LINES, COLUMNS);

    fclose(file);

}

/**
 * @brief Writes both stdev and means matrixes to a file.
 * */
void writeSummariesToCsv() {

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
    writeMatrixToFile(&means[0][0], file, CLASSES, COLUMNS - 1);
    writeMatrixToFile(&stdevs[0][0], file, CLASSES, COLUMNS - 1);

    // Closing files
    fclose(file);

}

/**
 * @brief Loads a CSV file into the summaries (means and stdevs) arrays.
 *
 * Searchs for a CSV file into the directory summaries matching the DATASET.
 * If DATASET equals pima, the CSV file that file summaries/pima.csv will be searched.
 * It throws an error if the file is not found. This file must contain n lines of attributes, where
 * the first n/2 lines represents the means and the remaining n/2 lines represents the standard deviations.
 * */
void loadSummariesFromCsv() {

    FILE *file; // Pointers to the files
    char path[30] = SUMMARIES_DIR; // Path to file
    int c; /* Last read character */
    char buffer[15]; /* Holds the current character in the file */
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