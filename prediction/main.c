/**
 * @file    prediction/main.c
 * @author  Alan Jeferson and Levi Moreira
 * @version V1.1.0
 * @date    23-August-2016
 * @brief   Main program body, entry point for the prediction module.
 * */


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "../defines.h"
#include "prediction.h"
#include "../util.h"
#include "csv.h"


/**
  * @brief Main function.
  *
  * This function executes the following steps:
  * 1. Loads a test dataset located at ../datasets/test/DATASET.csv;
  * 2. Loads the knowledge contained in the summaries CSV file, located at ../datasets/summaries/DATASET.csv;
  * 3. Calculates the metrics, that is to say, calculates the recall, precison and accuracy for each class in the dataset;
  * 4. Print the just calculated metrics;
  * 5. Predicts the class of a random set of attribute values in the test data set;
  **/
int main(int argc, char *argv[]) {


    srand(time(NULL));

    printf("\nRunning Naive Bayes in Dataset: %s\n\n", DATASET);
 clock_t begin = clock();
    /* Calculates Recall and Precision for classes */
    calculateMetrics();
   

    /* Loading the summaries */
    loadSummariesFromCsv();
    
    /* Loading the test set */
    loadTestsetFromCsv();


    /* Print confusion matrix for the model */
    printConfusionMatrix();

    /* Show the metrics for the model */
    printMetrics();
    clock_t end = clock();
    double time_spent = (double)(end - begin);
    
    printf("Loading time: %f",time_spent);
    return 0;
}
