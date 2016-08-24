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
  * ./naive PATH_TO_DATATSET NUMBER_OF_SAMPLES NUMBER_OF_FEATURES+1 NUMBER_OF_CLASSES
  * This program should only be used with numerical datasets of integer/float numbers
  *
  ******************************************************************************
  */

#include "main.h"
#include "util.h"
#include "learning.h"


int main(int argc, char *argv[]) {

    loadCsv();
    printf("Split %d rows into train=%d and test=%d rows\n", LINES, TRAINING_LINES, TEST_LINES);
    calculateSummaries();
    printf("Model Accuracy for the above split: %f%%\n", getAccuracy());
    

    return 0;
}