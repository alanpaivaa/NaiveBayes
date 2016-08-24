/**
  ******************************************************************************
  * @file    util.c
  * @author  Alan Jeferson and Levi Moreira
  * @version V1.0
  * @date    23-August-2016
  * @brief   This file provides all the utilities functions implementations
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "util.h"
#include "main.h"

  
  

/**
 * @brief Prints to the console the training dataset.
 * */
void printTrainingSet() {
    int i, j;
    for (i = 0; i < TRAINING_LINES; i++) {
        for (j = 0; j < COLUMNS; j++) {
            printf("%f", trainingSet[i][j]);
            if(j < COLUMNS - 1) {
                printf(", ");
            }
        }
        printf("\n");
    }
}


/**
 * @brief Prints to the console the test dataset.
 * */
void printTestset() {
    int i, j;
    for (i = 0; i < TEST_LINES; i++) {
        for (j = 0; j < COLUMNS; j++) {
            printf("%f", testSet[i][j]);
            if(j < COLUMNS - 1) {
                printf(", ");
            }
        }
        printf("\n");
    }
}


/**
 * @brief Loads the values from a CSV file into the training and data sets according to the
 * training ratio.
 * */
void loadCsv() {

    int c;
    char buffer[10]; /**<  Holds the current character in the file */
    char bc = 0; /**<  Counter for the buffer, for appending new characters each time */
    int dc = 0; /**<  Counts the number of characters found, for choosing the proper set */
    FILE *file = fopen(PATH, "r"); /**<  Opening the file */

    // :(
    if(file == NULL) {
        printf("Could not open file\n");
        return;
    }

    /**<  While there's file to read */
    while((c = fgetc(file)) != EOF) {
        if(c == COMMA_ASCII || c == LINE_FEED_ASCII) { /**<  A new value is ready to go */
            buffer[bc] = '\0';
            if(dc < (TRAINING_LINES * COLUMNS)) { /**<  If the data still fits on the training set */
                *(&(trainingSet[0][0]) + dc) = atof(buffer);
            } else { /**<  Otherwise, it fits on the test set */
                *(&(testSet[0][0]) + (dc - (TRAINING_LINES * COLUMNS))) = atof(buffer);
            }
            dc++;
            bc = 0;
        } else {
            buffer[bc++] = c;
        }
    }

    /**<  Making sure that the last character is read */
    if(bc > 0) {
        buffer[bc] = '\0';
        *(&(testSet[0][0]) + (dc - (TRAINING_LINES * COLUMNS))) = atof(buffer);
    }

    /**<  Close the file */
    fclose(file);
}

/**
 * @brief Prints the summaries to the console
 * */
void printSummaries() {

    int i, j;
    for (i = 0; i < CLASSES; i++) {
        printf("Classe %d:\n", i);
        for (j = 0; j < COLUMNS - 1; j++) {
            printf("(%11.6f, %11.6f)\n", means[i][j], stdevs[i][j]);
        }
        printf("\n");
    }

}