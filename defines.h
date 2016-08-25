//
// Created by Alan Jeferson on 24/08/16.
//

#ifndef UNTITLED_DEFINES_H
#define UNTITLED_DEFINES_H

/**
 * Useful defines.
 * */
#define COMMA_ASCII 44
#define LINE_FEED_ASCII 10
#define TRAINING_RATIO 0.8  //determine the split ratio
#define RANDOM_SETS 0       //determine if data is split randmonly (1) or not (0)
#define PI 3.141592653589793

#define TESTSET_DIR "training/datasets/test"
#define SUMMARIES_DIR "training/summaries"

/**
 * Pima dataset
 * */
//#define DATASET "pima"
//#define LINES 768
//#define COLUMNS 9
//#define CLASSES 2

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
#define DATASET "libras"
#define LINES 91
#define COLUMNS 240
#define CLASSES 10



#define TRAINING_LINES ((int) ((LINES * TRAINING_RATIO) + 1))
#define TEST_LINES (LINES - TRAINING_LINES)


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
