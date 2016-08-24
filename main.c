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
#include "main.h"
#include "util.h"
#include "learning.h"



void printMetrics()
{
    printf("\n------------------Metrics for the Model------------------\n");
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

/*
* @brief Calculates the k-fold cross Accuracy for the whole dataset. This function is used for test purposes only.
* @param The size of the fold (normally 10)
* @return The mean accuracy for the fold
*/
float getCrossAccuracy(int fold)
{
    int i;
    float cumulativeAccuracy = 0;
    float currentAccuracy = 0;
    for(i = 0; i<fold; i++)
    {
       // srand(time(0)+i*123);
        loadCsv();
        calculateSummaries();
        currentAccuracy = getAccuracy();
        printf("%2.2f\n",currentAccuracy);
        cumulativeAccuracy+=currentAccuracy;
    }

    return cumulativeAccuracy/10;
}


int main(int argc, char *argv[]) {
  
    /* Load up data and fill in the datasets in memory*/
    loadCsv(); 
    printf("\nSplit %d rows into train=%d and test=%d rows\n", LINES, TRAINING_LINES, TEST_LINES);

    /* Sumarize data*/
    calculateSummaries();

    calculateMetrics();
    printConfusionMatrix();
    /* Calculate the model accuracy*/
    
    printMetrics();
    //printf("Cross Accuracy for model: %f%%\n", getCrossAccuracy(10));

    return 0;
}