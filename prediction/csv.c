/**
 * @file    prediction/csv.c
 * @author  Alan Jeferson and Levi Moreira
 * @version V1.0
 * @date    23-August-2016
 * @brief   This file contains functions used to handle
 *          CSV files related to the prediction (loading test set and summaries).
 * */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../defines.h"


/**
 * @brief Loads the test dataset from a CSV file.
 *
 * The test dataset is loaded from ../datasets/test/DATASET.csv and put into
 * the testset matrix.
 * */
void loadTestsetFromCsv() {

    int c; /* Last read character */
    char buffer[15]; /* Holds the current character in the file */
    char bc = 0; /* Counter for the buffer, for appending new characters each time */
    char path[50] = TESTSET_DIR;
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
 * @brief Loads a CSV file into the summaries (means and stdevs) arrays.
 *
 * The CSV file is loaded from ../datasets/summaries/DATASET.csv and put into
 * the means and stdevs matrix.
 * */
void loadSummariesFromCsv() {

    FILE *file; // Pointers to the files
    char path[50] = SUMMARIES_DIR; // Path to file
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