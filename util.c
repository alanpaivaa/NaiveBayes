/**
 * @file    util.c
 * @author  Alan Jeferson and Levi Moreira
 * @version V1.1.0
 * @date    25-August-2016
 * @brief   This file contains the implementations for the
 *          auxiliar functions, i.e. print functions.
 * */

#include <stdio.h>
#include "util.h"
#include "defines.h"


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
 * @brief Prints the summaries to the console.
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


/**
 * @brief Prints the confusion matrix of the model.
 * */
void printConfusionMatrix()
{
    printf("------------------Confusion Matrix for the Model------------------\n");
    int i, j;

    printf("          ");
    for(i = 0; i<CLASSES; i++)
    {
	printf(" C%d   ",i);
    }
    printf("\n");
    for(i = 0; i<CLASSES;i++)
    {
        printf("Class %d |",i);
        for(j = 0; j<CLASSES;j++)
            printf("  %d   ",confusionMatrix[i][j] );
        printf("\n");
    }
}

/**
* @brief Prints a given line from the test set.
* @param The line index to be printed.
**/
void printTestSetLine(int line)
{
    int i;
    for(i = 0; i<COLUMNS; i++)
    {
        printf("%2.2f, ",testSet[line][i]);
    }
}
