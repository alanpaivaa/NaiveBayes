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
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "defines.h"
#include "csv.h"
#include "learning.h"
#include "util.h"
#include "extra.h"


/**
  * Main function
  **/
int main(int argc, char *argv[]) {


    srand(time(NULL));

    /* Load up data and fill in the datasets in memory*/
    loadCsv();
    printf("\nSplit %d rows into train=%d and test=%d rows\n", LINES, TRAINING_LINES, TEST_LINES);

    /* Sumarize data*/
    calculateSummaries();
//    printSummaries();
//    writeSummariesCsv();

//
//    /*Calculates Recall and Precision for classes*/
    calculateMetrics();
//
//    /*Print confusion matrix for the model*/
    printConfusionMatrix();
//
//    /* Show the metrics for the model*/
    printMetrics();
//
//    /*Show off the prediction skills*/
    showOff(rand()%TEST_LINES);

//    loadSummariesFromCsv();
//    printSummaries();


    return 0;
}