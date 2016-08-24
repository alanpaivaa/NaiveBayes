/**
  ******************************************************************************
  * @file    main.h
  * @author  Alan Jeferson and Levi Moreira
  * @version V1.0
  * @date    23-August-2016
  * @brief   This is the header file for the main
  * @note 	 This file contains the definitions of the main variables in the program.
  *
  ******************************************************************************
  */

#ifndef __MAIN_H
#define __MAIN_H



/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * Useful defines.
 * */
#define COMMA_ASCII 44
#define LINE_FEED_ASCII 10
#define TRAINING_RATIO 0.7
#define RANDOM_SETS 0
#define PI 3.141592653589793

/**
 * Pima dataset
 * */
#define PATH "datasets/pima.csv"
#define LINES 768
#define COLUMNS 9
#define CLASSES 2
#define TRAINING_LINES ((int) ((LINES * TRAINING_RATIO) + 1))
#define TEST_LINES (LINES - TRAINING_LINES)

/*
 * Column dataset.
 */
//#define PATH "datasets/column.csv"
//#define LINES 310
//#define COLUMNS 7
//#define CLASSES 2

/*
 * Iris dataset.
 */
//#define PATH "datasets/iris.csv"
//#define LINES 150
//#define COLUMNS 5
//#define CLASSES 3

/*
 * Wine dataset.
 * /
//#define PATH "datasets/wine.csv"
//#define LINES 178
//#define COLUMNS 14
//#define CLASSES 3



/**
 * trainingSet - Matrix that contains the training data, that will be used to make predictions
 **/
float trainingSet[TRAINING_LINES][COLUMNS];
/**
 * testSet - Holds the data that will be tested after the training
 **/
float testSet[TEST_LINES][COLUMNS];
/**
 * means - Holds all the means values used on the training
 **/
float means[CLASSES][COLUMNS - 1];
/** 
 * stdevs - Holds all the standard deviation value used on the training
 **/
float stdevs[CLASSES][COLUMNS - 1];

int confusionMatrix[CLASSES][CLASSES];


#endif /* __MAIN_H */