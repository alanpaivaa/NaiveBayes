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

#define DATASET_DIR "../datasets/full"
#define TESTSET_DIR "../datasets/test"
#define SUMMARIES_DIR "../datasets/summaries"


/*
 * MultiFeature dataset.
 */
//#define DATASET "mfeat"
//#define LINES 2000
//#define COLUMNS 77
//#define CLASSES 10

/*
 * Urbanland dataset.
 */
#define DATASET "urbanland"
#define LINES 168
#define COLUMNS 148
#define CLASSES 9

/*
 * Libras
 */
//#define DATASET "libras"
//#define LINES 240
//#define COLUMNS 91
//#define CLASSES 10



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


#endif //UNTITLED_DEFINES_H
