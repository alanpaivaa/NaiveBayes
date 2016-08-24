/**
  ******************************************************************************
  * @file    learning.c
  * @author  Alan Jeferson and Levi Moreira
  * @version V1.0
  * @date    23-August-2016
  * @brief   This file provides all the machine learning functions implementations
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "learning.h"
#include "main.h"

/**
 * Calculates the mean/avarage of a column of attributes considering they belong to a certain class
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
 * Calculates the standard deviation of a column that belongs to a class.
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
 * Calculates the summaries of the data and saves them to the correct arrays
 * The second part fo the Naive Bayes algorithm is to summarize the dataset.
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





/**
 * Calculates the probability of a given number belonging to a distribution based on the gaussian:
 * p = 1/(sqrt(2*PI*stdev)) * e^-(((x- mean)^2)/(2*(stdev^2)))
 * Where stdev is the standard deviation of the column and class to which x belongs to
 * Where mean is the mean of the column and class to which x belongs to
 * @param float x - the input value to be evaluated by the formula
 * @param float mean - the mean value of the column and class to which x belongs to
 * @param float stdev - the standard deviation of the column and class to which x belongs to
 * @return return the likelihood (in probability domain) of x belonging to the distribution represented by mean and stdev
*/
float calculateProbability(float x, float mean, float stdev)
{
    float exponent = exp(-(pow(x-mean,2)/(2*pow(stdev,2))));
    return (1 / (sqrt(2*PI) * stdev)) * exponent;
}


/**
 * Calculates the total probability of a certain class based on single probabilities yielded by each feature
 * @param int classNumber - The class to be considered
 * @return the cumulative probability of that class
*/
float calculateClassProbability(int classNumber, float *inputVector)
{
    int i;
    float classProbability = 1;
    /*  for each feature, calculate the probability and multiply them together */
    for(i = 0; i<COLUMNS-1; i++)
    {
        /*  considering the Bayes criterion, the total probability is the product of each single probability */
        classProbability*=calculateProbability(inputVector[i], means[classNumber][i], stdevs[classNumber][i] );
    }

    return classProbability;

}


/**
 * Predicts to which class the input vector belongs. Basically, runs over the probabilities for each class
 * and returns the highest one.
 * @return the predicted class to which the input vector belongs.
 * */
int predict(float *inputVector) {

    int i;

    /*  Probability of a class in each loop */
    float classProb;

    /*  Holds the highest probability */
    float bestProb = -1;

    /*  Holds the number of class which has the highest probability */
    int bestLabel = -1;

    for(i = 0; i < CLASSES; i++) {
        classProb = calculateClassProbability(i, inputVector); /*  Calculating the probability for the current class on the loop */
        if(classProb > bestProb) { /*  Checking if the new class' probability is higher than the highest known probability */
            bestProb = classProb;
            bestLabel = i;
        }
    }

    return bestLabel;

}

/**
 * Makes predicions based on the test set and then calculate the percentage of hits
 * @return The percentage of right predictions on the test set.
 * */
void calculateMetrics() {

    int i,j;

    for(i = 0; i<CLASSES; i++)
    {
        for(j = 0; j<CLASSES; j++)
            confusionMatrix[i][j] = 0;
    }

    /*  Number of correct predictions */
    int correct = 0;

    /*  Holds the current prediction on the loop */
    int prediction;

    for(i = 0; i < TEST_LINES; i++) {
        prediction = predict(testSet[i]); /*  Gets the prediction for a given test set line */
        confusionMatrix[(int)testSet[i][COLUMNS-1]][prediction]++;
        //if(prediction == (int) testSet[i][COLUMNS - 1]) { /*  Checks if the prediction hits */
          //  correct++;
        //}
    }

    /*  Returns the percentage of hits */
    //return (((float) correct) / TEST_LINES) * 100;

}


float getAccuracy()
{
    int i;
    int hits = 0;
    for(i = 0; i<CLASSES; i++)
    {
        hits+=confusionMatrix[i][i];
    }

    return (hits/(float)TEST_LINES)*100;
}
