/**
 * @file    prediction/prediction.c
 * @author  Alan Jeferson and Levi Moreira
 * @version V1.0
 * @date    23-August-2016
 * @brief   This file contains functions that execute predictions, test accuracy etc
 *          on the knowledge (summaries) with the test data set.
 * */


#include<stdio.h>
#include "../defines.h"
#include "math.h"


/**
 * @brief Calculates the probability of a given number belonging to a distribution based on the gaussian:
 * @note p = 1/(sqrt(2*PI*stdev)) * e^-(((x- mean)^2)/(2*(stdev^2)))
 * Where stdev is the standard deviation of the column and class to which x belongs to.
 * Where mean is the mean of the column and class to which x belongs to.
 * @param[in] float x The input value to be evaluated by the formula.
 * @param[in] float mean The mean value of the column and class to which x belongs to.
 * @param[in] float stdev The standard deviation of the column and class to which x belongs to.
 * @returns The likelihood (in probability domain) of x belonging to the distribution represented by mean and stdev.
 * */
float calculateProbability(float x, float mean, float stdev)
{
    double exponent = exp(-(pow(x-mean,2)/(2*pow(stdev,2))));
    
    double res = (1 / (sqrt(2*PI) * stdev)) * exponent;
    if(res == 0.0)
    {
     return 0.0;
    }
    else
    {
      return log(res);
    }
}


/**
 * @brief Calculates the total probability of a certain class based on single probabilities yielded by each feature.
 * @param[in] int classNumber The class to be considered
 * @returns the cumulative probability of that class
 * */
float calculateClassProbability(int classNumber, float *inputVector)
{
    int i;
    float classProbability = 0;
    /*  for each feature, calculate the probability and multiply them together */
    for(i = 0; i<COLUMNS-1; i++)
    {
        /*  considering the Bayes criterion, the total probability is the product of each single probability */
        classProbability+=calculateProbability(inputVector[i], means[classNumber][i], stdevs[classNumber][i] );
    }

    return classProbability;

}


/**
 * @brief Predicts to which class the input vector belongs.
 *
 * Basically, runs over the probabilities for each class
 * and returns the highest one.
 *
 * @param[in] float* inputVector The pointer to the vector to predict the class. The input vector
 * must me a set of values with the (COLUMNS - 1) columns. It is a set of attributes for the algorithm to predict
 * based on the knowledge it has calculated.
 * @return The predicted class to which the input vector belongs.
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
	
	if((bestLabel==-1) || (classProb > bestProb)) { /*  Checking if the new class' probability is higher than the highest known probability */
            bestProb = classProb;
            bestLabel = i;  
        }
    }
        
    return bestLabel;

}


/**
 * @brief Fills in the values in the confusion matrix.
 * @note The size of the Confusion Matrix is determined by the number of possible classes.
 * A confusion matrix for a 2 class model is:
 *                      Predicted Class 0           Predicted Class 1
 * Entry is of Class 0  True positives              False Negatives
 * Entry is of Class 1  False positives             True Negatives
 *
 * */
void calculateMetrics()
{

    int i,j;

    for(i = 0; i<CLASSES; i++)
    {
        for(j = 0; j<CLASSES; j++)
            confusionMatrix[i][j] = 0;
    }

    /*  Holds the current prediction on the loop */
    int prediction;

    for(i = 0; i < TEST_LINES; i++) {
        prediction = predict(testSet[i]); /*  Gets the prediction for a given test set line */
        confusionMatrix[(int)testSet[i][COLUMNS-1]][prediction]++;
    }

}


/**
 * @brief Makes predicions based on the test set and then calculate the percentage of hits.
 * @returns The percentage of right predictions on the test set.
 * */
float getAccuracy() {

    int i;

    /*  Number of correct predictions */
    int correct = 0;

    /*  Holds the current prediction on the loop */
    int prediction;

    for(i = 0; i < TEST_LINES; i++) {
        prediction = predict(testSet[i]); /*  Gets the prediction for a given test set line */
	
        if(prediction == (int) testSet[i][COLUMNS - 1]) { /*  Checks if the prediction hits */
            correct++;
        }
    }

    /*  Returns the percentage of hits */
    return (((float) correct) / TEST_LINES) * 100;

}


/**
 * @brief Analyzes the Confusion Matrix outputed by the model and calculates the recall.
 * @note The recall, or sensibility reveals the capability of the model to correclty predict a class in the cases
 * in which a data entry belongs to that class.
 * @return The true positives over the sum of true positves and false negatives
 * */
float getRecall(int class)
{
    int i;
    int sum = 0;
    for(i = 0; i<CLASSES;i++)
    {
        sum+=confusionMatrix[class][i];
    }

    return (confusionMatrix[class][class]/(float)sum);
}

/**
 * @brief Analyzes the Confusion Matrix outputed by the model and calculates the precision.
 * @note The precision, or specificity reveals the capability of the model to correclty predict a class in the cases
 * in which a data entry doesn't belong to that class.
 * @return The true negatives over the sum of true negatives and false positives
 * */
float getPrecision(int class) {
    int i;
    int sum = 0;
    for(i = 0; i<CLASSES;i++)
    {
        sum+=confusionMatrix[i][class];
    }
    return (confusionMatrix[class][class]/(float)sum);
}

/**
 * @brief print out the metrics (Recall, Precision and Accuracy for the model).
 * @note Please note that the Recall and Precision are printed by class and the Accuracy is for the whole model.
 * */
void printMetrics()
{
    printf("\n------------------Metrics for the Model---------------------------\n");
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