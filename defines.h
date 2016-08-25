/**
  ******************************************************************************
  * @file    defines.h
  * @author  Alan Jeferson and Levi Moreira
  * @version V1.1.0
  * @date    25-August-2016
  * @brief   This file contains all the variables and defines that will be used on the program.
  * @note    You can find here variables like the trainning and test sets and the summaries (means
  * and standard deviation variables). You can also choose the proper data set and ratio for the training
  * set.
  ******************************************************************************
*/

#ifndef UNTITLED_DEFINES_H
#define UNTITLED_DEFINES_H

/**
 * Useful defines.
 * */
#define COMMA_ASCII 44              /** The ascii value for the commma character. */
#define LINE_FEED_ASCII 10          /** The ascii value for the line break character. */
#define TRAINING_RATIO 0.7          /** The ratio that will be used to splid the dataset into training and test sets. */
#define RANDOM_SETS 1               /** Determines wheter or not to use random sets. If set to 0, the first part of the dataset will be for training
                                      * and the second part will be for testing. If set to 1, the set and training sets will be chosen randomly. */
#define PI 3.141592653589793        /** The PI constant. */

#define DATASET_DIR "datasets"      /** Name of the directory in which the datasets go. */
#define TESTSET_DIR "datasets/test" /** Name of the direcoty in which the test datasets go. */
#define SUMMARIES_DIR "summaries"   /** Name of the directory in which the summaries calculated from the dataset go. */

/**
 * Pima dataset
 * */
#define DATASET "pima"              /** The name of the current dataset. */
#define LINES 768                   /** The number of lines in the current dataset. */
#define COLUMNS 9                   /** The number of attributes in the dataset plus 1 (that represents the class value). */
#define CLASSES 2                   /** The number of classes present in the dataset. */

/*
 * Column dataset.
 */
//#define DATASET "column"
//#define LINES 310
//#define COLUMNS 7
//#define CLASSES 2

/*
 * Iris dataset.
 */
//#define DATASET "iris"
//#define LINES 150
//#define COLUMNS 5
//#define CLASSES 3

/*
 * Wine dataset.
 */
//#define DATASET "wine"
//#define LINES 178
//#define COLUMNS 14
//#define CLASSES 3



#define TRAINING_LINES ((int) ((LINES * TRAINING_RATIO) + 1))
#define TEST_LINES (LINES - TRAINING_LINES)

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

/**
 * confusionMatrix - Holds the confusion matrix values for the dataset
 **/
int confusionMatrix[CLASSES][CLASSES];

#endif //UNTITLED_DEFINES_H
