//
// Created by Alan Jeferson on 24/08/16.
//

#include<math.h>
#include "defines.h"

/**
 * @brief Calculates the mean/avarage of a column of attributes considering they belong to a certain class
 * @param int classNumber - The number of the class to be considered
 * @param int columnNumber - The column of attributes about which the mean will be calculated
 * @return Returns a float with the average of the values of the column considering the class number
*/
float calculateMean(int classNumber, int columnNumber)
{
    int i;

    /* holds the amount of values used in the calculation*/
    int total = 0;

    /* holds the sum of the values used in the calculation */
    float values = 0;

    /* Calculate the mean only for the training data, the first 70% values of the dataset */
    for(i = 0; i < TRAINING_LINES; i++)
    {
        /* if the data is from the correct class, then add it to the mean calculation */
        if(trainingSet[i][COLUMNS-1]==classNumber)
        {
            values+=trainingSet[i][columnNumber];
            total++;
        }

    }

    return values/(float)(total);

}


/**
 * @brief Calculates the standard deviation of a column that belongs to a class.
 * @param classNumber - The number of the class to make the calculation.
 * @param columnNumber - The column that indicates which attribute will be considered.
 * @param mean - The mean for the same class and column numbers above.
 * */
float calculateStdev(int classNumber, int columnNumber, float mean) {

    int i;

    /*  The variance for the given classNumber and columnNumber */
    float variance = 0;

    /*  Counter for the number of elements to be able to derive the standard deviation */
    float count = 0;

    /*  Iterating over the training set */
    for(i = 0; i < TRAINING_LINES; i++) {

        /*  Checks if the current loop is at the chosen class */
        if(trainingSet[i][COLUMNS - 1] == classNumber) {
            variance += pow(trainingSet[i][columnNumber] - mean, 2);
            count += 1;
        }
    }

    /*  Deriving the standard deviation from variance and count */
    return sqrt(variance/(count - 1));

}


/**
 * @brief Calculates the summaries of the data and saves them to the correct arrays
 * @note The second part fo the Naive Bayes algorithm is to summarize the dataset.
 * The summaries are the means and standard deviations of the data separated by class
 * Two subarrays are used to hold the summaries, their sizes are NUMBER_OF_CLASSES*NUMBER_OF_FEATURES
 * Therefore the first line of the arrays contain the summaries for the first class and so on and so forth
*/
void calculateSummaries()
{
    int i,j;
    for(i = 0; i<CLASSES;i++) /*  Iterate through classes */
    {
        for(j = 0; j<COLUMNS-1;j++) /*  Iterate through features */
        {
            means[i][j] = calculateMean(i, j);
            stdevs[i][j] = calculateStdev(i, j, means[i][j]);
        }

    }
}

