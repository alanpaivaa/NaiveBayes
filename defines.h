/**
 * @file    defines.h
 * @author  Alan Jeferson and Levi Moreira
 * @version V1.0
 * @date    25-August-2016
 * @brief   This file contains all the global variables that are used on the entire program,
 *          in both training and predictions modules.
 * */

#ifndef UNTITLED_DEFINES_H
#define UNTITLED_DEFINES_H

#define COMMA_ASCII 44                          /**< The ASCII code for the comma character. */
#define LINE_FEED_ASCII 10                      /**< The ASCII code for the line break character. */
#define TRAINING_RATIO 0.8                      /**< The percentage of the dataset that is destined for training. */
#define RANDOM_SETS 0                           /**< Indicates if the sets are build randomly or divided in halves. */
#define PI 3.141592653589793                    /**< The Pi constant. */

#define DATASET_DIR "../datasets/full"          /**< Path where the full datasets are located. */
#define TESTSET_DIR "../datasets/test"          /**< Path where the test datasets are locatd. */
#define SUMMARIES_DIR "../datasets/summaries"   /**< Path where the summaries are located. */


/**
 * MultiFeature dataset.
 * */
#define DATASET "mfeat"                         /**< Current dataset's name */
#define LINES 2000                              /**< The number of lines in the current dataset. */
#define COLUMNS 77                              /**< The number of attributes in the current dataset plus a class value. */
#define CLASSES 10                              /**< The number of classes in the dataset. */

/**
 * Urbanland dataset.
 * */
//#define DATASET "urbanland"
//#define LINES 168
//#define COLUMNS 148
//#define CLASSES 9

/**
 * Libras
 * */
//#define DATASET "libras"
//#define LINES 240
//#define COLUMNS 91
//#define CLASSES 10



#define TRAINING_LINES ((int) ((LINES * TRAINING_RATIO) + 1))       /**< The number of lines in the training dataset. */
#define TEST_LINES (LINES - TRAINING_LINES)                         /**< The number of lines in the test dataset. */

float trainingSet[TRAINING_LINES][COLUMNS];                         /**< Matrix that contains the training data, that will be used to make predictions */
float testSet[TEST_LINES][COLUMNS];                                 /**< Holds the data that will be tested after the training */
float means[CLASSES][COLUMNS - 1];                                  /**< Holds all the means values used on the training */
float stdevs[CLASSES][COLUMNS - 1];                                 /**< Holds all the standard deviation value used on the training */
int confusionMatrix[CLASSES][CLASSES];                              /**< Holds the confusion matrix values for the dataset */

#endif //UNTITLED_DEFINES_H
