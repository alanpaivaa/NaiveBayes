/*This is a c implementation of the Machine Learning algorithm called Naive Bayes Gaussian. 
* It's been adapted from the python version in: http://machinelearningmastery.com/naive-bayes-classifier-scratch-python/ 
* It was created by Alan Jeferson and Levi Moreira.
* To run the program please place the desired dataset in the datasets folder and run the program :
*              ./naive PATH_TO_DATATSET NUMBER_OF_SAMPLES NUMBER_OF_FEATURES+1 NUMBER_OF_CLASSES
* This program should only be used with numerical datasets of integer/float numbers
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define COMMA_ASCII 44
#define LINE_FEED_ASCII 10

// Dataset Pima
#define PIMA_PATH "datasets/pima.csv"
#define PIMA_LINES 768
#define PIMA_COLUMNS 9
#define PIMA_CLASSES 2
#define PI  3.141592653589793


// Current dataset
const  int lines = PIMA_LINES;
const int rows = PIMA_COLUMNS;
const char *path = PIMA_PATH;
const int classes = PIMA_CLASSES;

/*float dataset[lines][rows];
float means[classes][rows-1];
float stdevs[classes][rows-1];
float inputVector[rows -1];*/

float dataset[PIMA_LINES][PIMA_COLUMNS];
float means[PIMA_CLASSES][PIMA_COLUMNS-1];
float stdevs[PIMA_CLASSES][PIMA_COLUMNS-1];
float inputVector[PIMA_COLUMNS -1];

void printDataset() {
    int i, j;
    for (i = 0; i < lines; i++) {
        for (j = 0; j < rows; j++) {
            printf("%f", dataset[i][j]);
            if(j < rows - 1) {
                printf(", ");
            }
        }
        printf("\n");
    }
}

void loadCsv() {

    FILE *file = fopen(path, "r");

    if(file == NULL) {
        printf("Could not open file\n");
        return;
    }

    int c;
    char buffer[10];
    char bc = 0;
    int dc = 0;
    while((c = fgetc(file)) != EOF) {
        if(c == COMMA_ASCII || c == LINE_FEED_ASCII) {
            buffer[bc] = '\0';
            *(&(dataset[0][0]) + dc) = atof(buffer);
            dc++;
            bc = 0;
        } else {
            buffer[bc++] = c;
        }
    }

    fclose(file);
}

/*
* Calculates the mean/avarage of a column of attributes considering they belong to a certain class
* @param int classNumber - The number of the class to be considered
* @param int columnNumber - The column of attributes about which the mean will be calculated
* @return Returns a float with the average of the values of the column considering the class number
*/
float calculateMean(int classNumber, int columnNumber)
{
    int i;

    //holds the amount of values used in the calculation
    int total = 0;

    //holds the sum of the values used in the calculation
    float values = 0;

    //Calculate the mean only for the training data, the first 70% values of the dataset
    for(i = 0; i<(int)(lines*0.7)+1; i++)
    {
        //if the data is from the correct class, then add it to the mean calculation
        if(dataset[i][rows-1]==classNumber)
        {
            values+=dataset[i][columnNumber];
            total++;
        }

    }

    return values/(float)(total);

}

float calculateStdev(int classNumber, int columnNumber, float mean) {

    int i;
    float variance = 0;
    float count = 0;

    for(i = 0; i < (int) (lines*0.7) + 1; i++) {
        if(dataset[i][rows - 1] == classNumber) {
            variance += pow(dataset[i][columnNumber] - mean, 2);
            count += 1;
        }
    }

    return sqrt(variance/(count - 1));

}

/*
* Calculates the summaries of the data and saves them to the correct arrays
* The second part fo the Naive Bayes algorithm is to summarize the dataset.
* The summaries are the means and standard deviations of the data separated by class
* Two subarrays are used to hold the summaries, their sizes are NUMBER_OF_CLASSES*NUMBER_OF_FEATURES
* Therefore the first line of the arrays contain the summaries for the first class and so on and so forth
*/

void calculateSummaries()
{
    int i,j;
    for(i = 0; i<classes;i++) // Iterate through classes
    {
        for(j = 0; j<rows-1;j++) // Iterate through features
        {
            means[i][j] = calculateMean(i, j);
            stdevs[i][j] = calculateStdev(i, j, means[i][j]);
        }

    }
}

void printSummaries() {

    int i, j;
    for (i = 0; i < classes; i++) {
        printf("Classe %d:\n", i);
        for (j = 0; j < rows - 1; j++) {
            printf("(%f, %f)\n", means[i][j], stdevs[i][j]);
        }
        printf("\n");
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
**/

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
float calculateClassProbability(int classNumber)
{
    int i;
    float classProbability = 1;
    //for each feature, calculate the probability and multiply them together
    for(i = 0; i<rows-1; i++)
    {
        //considering the Bayes criterion, the total probability is the product of each single probability
        classProbability*=calculateProbability(inputVector[i], means[classNumber][i], stdevs[classNumber][i] );
    }

    return classProbability;

}

/**
 * Predicts to which class the input vector belongs. Basically, runs over the probabilities for each class
 * and returns the highest one.
 * @return the predicted class to which the input vector belongs.
 * */
int predict() {

    int i;
    float classProb;
    float bestProb = -1;
    int bestLabel = -1;

    for(i = 0; i < classes; i++) {
        classProb = calculateClassProbability(i);
        if(classProb > bestProb) {
            bestProb = classProb;
            bestLabel = i;
        }
    }

    return bestLabel;

}

int main(int argc, char *argv[]) {

    loadCsv();
    calculateSummaries();
//    printSummaries();

    return 0;
}