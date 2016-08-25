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
#include <stdio.h>
#include "util.h"
#include "defines.h"
#include "prediction.h"
 

 /**
* @brief print out the metrics (Recall, Precision and Accuracy for the model)
* @note Please note that the Recall and Precision are printed by class and the Accuracy is for the whole model
**/
void printMetrics()
{
    printf("\n------------------Metrics for the Model---------------------------\n");
    int i;
    for(i = 0; i<CLASSES; i++)
    {
        printf("Metrics for Class %d\n", i);
        printf("Precision %2.2f\n", getPrecision(i));
        printf("Recall %2.2f\n",getRecall(i) );
        printf("\n");
    }

    printf("\nModel Accuracy for the above split: %f%%\n", getAccuracy());
}


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
 *@brief Prints the summaries to the console
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
*@brief Prints the confusion matrix of the model
*/
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
* @brief Prints a given line from the test set
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