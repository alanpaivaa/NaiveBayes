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

    int c; /* Last read character */
    char buffer[10]; /* Holds the current character in the file */
    char bc = 0; /* Counter for the buffer, for appending new characters each time */
    FILE *file = fopen(PATH, "r"); /* Opening the file */

    int count = COLUMNS; /* Tells the position of a character in a line */
    int trainingCount = -1; /* Line count for the training set */
    int testCount = -1; /* Line count for the test set */
    int selectedSet; /* 0 for training, 1 for test */
    int randomNumber;
    // :(
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

void printConfusionMatrix()
{
    printf("------------------Confusion Matrix for the Model------------------\n");
    int i, j;
    for(i = 0; i<CLASSES;i++)
    {
        printf("Class %d ",i);
        for(j = 0; j<CLASSES;j++)
            printf("  %d   ",confusionMatrix[i][j] );
        printf("\n");
    }
}

/**
* Prints a given line from the test set
* @param The line index to be printed
**/
void printTestSetLine(int line)
{
    int i;
    for(i = 0; i<COLUMNS; i++)
    {
        printf("%2.2f, ",testSet[line][i]);
    }
}