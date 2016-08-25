/**
  ******************************************************************************
  * @file    main.c 
  * @author  Alan Jeferson and Levi Moreira
  * @version V1.1.0
  * @date    23-August-2016
  * @brief   Main program body
  * @note This is a c implementation of the Machine Learning algorithm called Naive Bayes Gaussian.
  * It's been adapted from the python version in: http://machinelearningmastery.com/naive-bayes-classifier-scratch-python/
  * It was created by .
  * To run the program please place the desired dataset in the datasets folder and run the program :
  *  1) Compile gcc main.c learning.c util.c -o main -lm
  *  2) Run ./main
  * This program should only be used with numerical datasets of integer/float numbers
  *
  ******************************************************************************
  */

  
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "training.h"
#include "csv.h"

/**
  * Main function
  **/
int main(int argc, char *argv[]) {

    srand(time(NULL));

    loadFullDatasetFromCsv(); /* Loading an entire dataset */
    printf("CSV file loaded into training and test sets!\n");

    writeTestsetToCsv(); /* Writing the test set to a csv file */
    printf("Testset written to a CSV file!\n");

    calculateSummaries(); /* Calculating the summaries */
    printf("Summaries calculated!\n");

    writeSummariesToCsv(); /* Writing the summaries to a csv file */
    printf("Summaries written to a CSV file!\n");

    return 0;
}