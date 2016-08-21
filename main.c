/**
 * This is a c implementation of the Machine Learning algorithm called Naive Bayes Gaussian.
 * It's been adapted from the python version in: http://machinelearningmastery.com/naive-bayes-classifier-scratch-python/
 * It was created by Alan Jeferson and Levi Moreira.
 * To run the program please place the desired dataset in the datasets folder and run the program :
 * ./naive PATH_TO_DATATSET NUMBER_OF_SAMPLES NUMBER_OF_FEATURES+1 NUMBER_OF_CLASSES
 * This program should only be used with numerical datasets of integer/float numbers
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define COMMA_ASCII 44
#define LINE_FEED_ASCII 10
#define TRAINING_RATIO 0.7


/**
 * Pima dataset
 * */
#define PIMA_PATH "datasets/pima.csv"
#define PIMA_LINES 768
#define PIMA_COLUMNS 9
#define PIMA_CLASSES 2
#define PI  3.141592653589793


/**
 * Variables which define the behavior of the program.
 * */
const int totalLines = PIMA_LINES;
const int trainingLines = (int) ((totalLines * TRAINING_RATIO) + 1);
const int testLines = totalLines - trainingLines;
const int rows = PIMA_COLUMNS;
const char *path = PIMA_PATH;
const int classes = PIMA_CLASSES;


/**
 * trainingSet - Matrix that contains the training data, that will be used to make predictions
 * testSet - Holds the data that will be tested after the training
 * means - Holds all the means values used on the training
 * stdevs - Holds all the standard deviation value used on the training
 * */
float trainingSet[trainingLines][rows];
float testSet[testLines][rows];
float means[classes][rows-1];
float stdevs[classes][rows-1];


//float dataset[PIMA_LINES][PIMA_COLUMNS];
//float means[PIMA_CLASSES][PIMA_COLUMNS-1];
//float stdevs[PIMA_CLASSES][PIMA_COLUMNS-1];


/**
 * Prints to the console the training dataset.
 * */
void printTrainingSet() {
    int i, j;
    for (i = 0; i < trainingLines; i++) {
        for (j = 0; j < rows; j++) {
            printf("%f", trainingSet[i][j]);
            if(j < rows - 1) {
                printf(", ");
            }
        }
        printf("\n");
    }
}


/**
 * Prints to the console the test dataset.
 * */
void printTestset() {
    int i, j;
    for (i = 0; i < testLines; i++) {
        for (j = 0; j < rows; j++) {
            printf("%f", testSet[i][j]);
            if(j < rows - 1) {
                printf(", ");
            }
        }
        printf("\n");
    }
}


/**
 * Loads the values from a CSV file into the training and data sets according to the
 * training ratio.
 * */
void loadCsv() {

    int c;
    char buffer[10]; // Holds the current character in the file
    char bc = 0; // Counter for the buffer, for appending new characters each time
    int dc = 0; // Counts the number of characters found, for choosing the proper set
    FILE *file = fopen(path, "r"); // Opening the file

    // :(
    if(file == NULL) {
        printf("Could not open file\n");
        return;
    }

    // While there's file to read
    while((c = fgetc(file)) != EOF) {
        if(c == COMMA_ASCII || c == LINE_FEED_ASCII) { // A new value is ready to go
            buffer[bc] = '\0';
            if(dc < (trainingLines * rows)) { // If the data still fits on the training set
                *(&(trainingSet[0][0]) + dc) = atof(buffer);
            } else { // Otherwise, it fits on the test set
                *(&(testSet[0][0]) + (dc - (trainingLines * rows))) = atof(buffer);
            }
            dc++;
            bc = 0;
        } else {
            buffer[bc++] = c;
        }
    }

    // Close the file
    fclose(file);
}


/**
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
    for(i = 0; i < trainingLines; i++)
    {
        //if the data is from the correct class, then add it to the mean calculation
        if(trainingSet[i][rows-1]==classNumber)
        {
            values+=trainingSet[i][columnNumber];
            total++;
        }

    }

    return values/(float)(total);

}


/**
 * Calculates the standar deviation of a column that belongs to a class.
 * @param classNumber - The number of the class to make the calculation.
 * @param columnNumber - The column that indicates which attribute will be considered.
 * @param mean - The mean for the same class and column numbers above.
 * */
float calculateStdev(int classNumber, int columnNumber, float mean) {

    int i;

    // The variance for the given classNumber and columnNumber
    float variance = 0;

    // Counter for the number of elements to be able to derive the standard deviation
    float count = 0;

    // Iterating over the training set
    for(i = 0; i < trainingLines; i++) {

        // Checks if the current loop is at the chosen class
        if(trainingSet[i][rows - 1] == classNumber) {
            variance += pow(trainingSet[i][columnNumber] - mean, 2);
            count += 1;
        }
    }

    // Deriving the standard deviation from variance and count
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
    for(i = 0; i<classes;i++) // Iterate through classes
    {
        for(j = 0; j<rows-1;j++) // Iterate through features
        {
            means[i][j] = calculateMean(i, j);
            stdevs[i][j] = calculateStdev(i, j, means[i][j]);
        }

    }
}


/**
 * Prints the summaries to the console
 * */
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
int predict(float *inputVector) {

    int i;
    float classProb;
    float bestProb = -1;
    int bestLabel = -1;

    for(i = 0; i < classes; i++) {
        classProb = calculateClassProbability(i, inputVector);
        if(classProb > bestProb) {
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
float getAccuracy() {

    int i;
    int correct = 0;
    int prediction;

    for(i = 0; i < testLines; i++) {
        prediction = predict(testSet[i]);
        if(prediction == (int) testSet[i][rows - 1]) {
            correct++;
        }
    }
    return (((float) correct) / testLines) * 100;

}


int main(int argc, char *argv[]) {

    loadCsv();
    calculateSummaries();
    printf("%f%%\n", getAccuracy());

    return 0;
}