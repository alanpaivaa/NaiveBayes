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

/**
 * Useful defines.
 * */
#define COMMA_ASCII 44
#define LINE_FEED_ASCII 10
#define TRAINING_RATIO 0.7
#define PI 3.141592653589793

/**
 * Pima dataset
 * */
#define PATH "datasets/pima.csv"
#define LINES 768
#define COLUMNS 9
#define CLASSES 2

/**
 * Column dataset.
 * */
//#define PATH "datasets/column.csv"
//#define LINES 310
//#define COLUMNS 7
//#define CLASSES 2

/**
 * Iris dataset.
 * */
//#define PATH "datasets/iris.csv"
//#define LINES 150
//#define COLUMNS 5
//#define CLASSES 3

/**
 * Wine dataset.
 * */
//#define PATH "datasets/wine.csv"
//#define LINES 178
//#define COLUMNS 14
//#define CLASSES 3

#define TRAINING_LINES ((int) ((LINES * TRAINING_RATIO) + 1))
#define TEST_LINES (LINES - TRAINING_LINES)


/**
 * trainingSet - Matrix that contains the training data, that will be used to make predictions
 * testSet - Holds the data that will be tested after the training
 * means - Holds all the means values used on the training
 * stdevs - Holds all the standard deviation value used on the training
 * */
float trainingSet[TRAINING_LINES][COLUMNS];
float testSet[TEST_LINES][COLUMNS];
float means[CLASSES][COLUMNS - 1];
float stdevs[CLASSES][COLUMNS - 1];


/**
 * Prints to the console the training dataset.
 * */
void printTrainingSet() {
    int i, j;
    for (i = 0; i < TRAINING_LINES; i++) {
        for (j = 0; j < COLUMNS; j++) {
            printf("%f", trainingSet[i][j]);
            if(j < COLUMNS - 1) {
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
    for (i = 0; i < TEST_LINES; i++) {
        for (j = 0; j < COLUMNS; j++) {
            printf("%f", testSet[i][j]);
            if(j < COLUMNS - 1) {
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
    FILE *file = fopen(PATH, "r"); // Opening the file

    // :(
    if(file == NULL) {
        printf("Could not open file\n");
        return;
    }

    // While there's file to read
    while((c = fgetc(file)) != EOF) {
        if(c == COMMA_ASCII || c == LINE_FEED_ASCII) { // A new value is ready to go
            buffer[bc] = '\0';
            if(dc < (TRAINING_LINES * COLUMNS)) { // If the data still fits on the training set
                *(&(trainingSet[0][0]) + dc) = atof(buffer);
            } else { // Otherwise, it fits on the test set
                *(&(testSet[0][0]) + (dc - (TRAINING_LINES * COLUMNS))) = atof(buffer);
            }
            dc++;
            bc = 0;
        } else {
            buffer[bc++] = c;
        }
    }

    // Making sure that the last character is read
    if(bc > 0) {
        buffer[bc] = '\0';
        *(&(testSet[0][0]) + (dc - (TRAINING_LINES * COLUMNS))) = atof(buffer);
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
    for(i = 0; i < TRAINING_LINES; i++)
    {
        //if the data is from the correct class, then add it to the mean calculation
        if(trainingSet[i][COLUMNS-1]==classNumber)
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
    for(i = 0; i < TRAINING_LINES; i++) {

        // Checks if the current loop is at the chosen class
        if(trainingSet[i][COLUMNS - 1] == classNumber) {
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
    for(i = 0; i<CLASSES;i++) // Iterate through classes
    {
        for(j = 0; j<COLUMNS-1;j++) // Iterate through features
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
    for (i = 0; i < CLASSES; i++) {
        printf("Classe %d:\n", i);
        for (j = 0; j < COLUMNS - 1; j++) {
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
    for(i = 0; i<COLUMNS-1; i++)
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

    // Probability of a class in each loop
    float classProb;

    // Holds the highest probability
    float bestProb = -1;

    // Holds the number of class which has the highest probability
    int bestLabel = -1;

    for(i = 0; i < CLASSES; i++) {
        classProb = calculateClassProbability(i, inputVector); // Calculating the probability for the current class on the loop
        if(classProb > bestProb) { // Checking if the new class' probability is higher than the highest known probability
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

    // Number of correct predictions
    int correct = 0;

    // Holds the current prediction on the loop
    int prediction;

    for(i = 0; i < TEST_LINES; i++) {
        prediction = predict(testSet[i]); // Gets the prediction for a given test set line
        if(prediction == (int) testSet[i][COLUMNS - 1]) { // Checks if the prediction hits
            correct++;
        }
    }

    // Returns the percentage of hits
    return (((float) correct) / TEST_LINES) * 100;

}


int main(int argc, char *argv[]) {

    loadCsv();
    calculateSummaries();
    printf("Split %d rows into train=%d and test=%d rows\n", LINES, TRAINING_LINES, TEST_LINES);
    printf("Accuracy: %f%%\n", getAccuracy());

    return 0;
}