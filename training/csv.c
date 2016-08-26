/**
 * @file    training/csv.c
 * @author  Alan Jeferson and Levi Moreira
 * @version V1.1.0
 * @date    25-August-2016
 * @brief   This file contains functions for handling CSV files,
 *          i.e. loading and writing from an to files.
 * */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../defines.h"


/**
 * @brief Loads the values from a CSV file into the training and data sets according to the
 * training ratio.
 *
 * Loads the CSV file located in ../datasets/full/DATASET.csv. This is a full dataset, therefore
 * it is necessary to split this data set into test and training data set. This function makes this
 * splitting and saves the values read from the CSV file in the proper matrixes (testSet and trainingSet).
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
 * @brief Writes the given summary array to a file.
 *
 * Write and matrix with the given lines and columns in a file pointed by the given pointer.
 * @param[out] vector The matrix whose values will be written on the file.
 * @param[out] file The pointer to file where the data will be written.
 * @param[in] lines The number of lines in the matrix.
 * @param[in] columns The number of columns in the matrix.
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
 * */
void writeTestsetToCsv() {

    FILE *file; // Pointer to the files
    char path[50] = TESTSET_DIR; // Path to file

    // Opening the file
    strcat(path, "/");
    strcat(path, DATASET);
    strcat(path, ".csv");
    file = fopen(path, "w");

    // Checking if the file opened correctly
    if(file == NULL) {
        printf("Could not open the file to write testset :(\n");
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
    char path[50] = SUMMARIES_DIR; // Path to file

    // Opening the file
    strcat(path, "/");
    strcat(path, DATASET);
    strcat(path, ".csv");
    file = fopen(path, "w");

    // Checking if the file opened correctly
    if(file == NULL) {
        printf("Could not open the file to write summaries:(\n");
        return;
    }

    // Writing the file
    writeMatrixToFile(&means[0][0], file, CLASSES, COLUMNS - 1);
    writeMatrixToFile(&stdevs[0][0], file, CLASSES, COLUMNS - 1);

    // Closing files
    fclose(file);

}