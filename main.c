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
#define PIMA_PATH "datasets/pima.csv"
#define PIMA_LINES 768
#define PIMA_COLUMNS 9
#define PIMA_CLASSES 2

/**
 * Column dataset.
 * */
#define COLUMN_PATH "datasets/column.csv"
#define COLUMN_LINES 310
#define COLUMN_COLUMNS 7
#define COLUMN_CLASSES 2

/**
 * Iris dataset.
 * */
#define IRIS_PATH "datasets/iris.csv"
#define IRIS_LINES 150
#define IRIS_COLUMNS 5
#define IRIS_CLASSES 3

/**
 * Wine dataset.
 * */
#define WINE_PATH "datasets/wine.csv"
#define WINE_LINES 178
#define WINE_COLUMNS 14
#define WINE_CLASSES 3


/**
 * Variables which define the behavior of the program.
 * */
 int totalLines = PIMA_LINES;
 int trainingLines = (int) ((PIMA_LINES * TRAINING_RATIO) + 1);
 int testLines = PIMA_LINES - (int) ((PIMA_LINES * TRAINING_RATIO) + 1);
 int columns = PIMA_COLUMNS;
 char *path = PIMA_PATH;
 int classes = PIMA_CLASSES;


/**
 * trainingSet - Matrix that contains the training data, that will be used to make predictions
 * testSet - Holds the data that will be tested after the training
 * means - Holds all the means values used on the training
 * stdevs - Holds all the standard deviation value used on the training
 * */
/*float trainingSet[trainingLines][columns];
float testSet[testLines][columns];
float means[classes][columns-1];
float stdevs[classes][columns-1];*/


float trainingSet[(int) ((PIMA_LINES * TRAINING_RATIO) + 1)][PIMA_COLUMNS];
float testSet[PIMA_LINES-(int) ((PIMA_LINES * TRAINING_RATIO) + 1)][PIMA_COLUMNS];
float means[PIMA_CLASSES][PIMA_COLUMNS-1];
float stdevs[PIMA_CLASSES][PIMA_COLUMNS-1];


/**
 * Prints to the console the training dataset.
 * */
void printTrainingSet() {
    int i, j;
    for (i = 0; i < trainingLines; i++) {
        for (j = 0; j < columns; j++) {
            printf("%f", trainingSet[i][j]);
            if(j < columns - 1) {
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
        for (j = 0; j < columns; j++) {
            printf("%f", testSet[i][j]);
            if(j < columns - 1) {
                printf(", ");
            }
        }
        printf("\n");
    }
}

/**
* Print specified line in the testset
*/

void printTestSetLine(int line)
{
    int i;
    for(i = 0; i<columns; i++)
    {
        printf("%2.2f, ",testSet[line][i]);
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
            if(dc < (trainingLines * columns)) { // If the data still fits on the training set
                *(&(trainingSet[0][0]) + dc) = atof(buffer);
            } else { // Otherwise, it fits on the test set
                *(&(testSet[0][0]) + (dc - (trainingLines * columns))) = atof(buffer);
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
        *(&(testSet[0][0]) + (dc - (trainingLines * columns))) = atof(buffer);
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
        if(trainingSet[i][columns-1]==classNumber)
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
        if(trainingSet[i][columns - 1] == classNumber) {
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
        for(j = 0; j<columns-1;j++) // Iterate through features
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
        for (j = 0; j < columns - 1; j++) {
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
    for(i = 0; i<columns-1; i++)
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

    for(i = 0; i < classes; i++) {
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

    for(i = 0; i < testLines; i++) {
        prediction = predict(testSet[i]); // Gets the prediction for a given test set line
        if(prediction == (int) testSet[i][columns - 1]) { // Checks if the prediction hits
            correct++;
        }
    }

    // Returns the percentage of hits
    return (((float) correct) / testLines) * 100;

}

/**
* Simply takes a certain entry of the test dataset and show the prediction for it so the user can see the algorithm working
* @param int testLine - A certain line of the test dataset
**/
void showOff(int testLine)
{
    printf("Showing off the prediction skills in the input vector: \n");
    printTestSetLine(testLine);
    int prediction = predict(testSet[testLine]);
    printf("\nPredicted class %d\n",prediction );
    if(prediction==testSet[testLine][columns-1])
    {
        printf("It's a hit :)\n");
    }else
    {
        printf("It's a miss :(\n");
    }


}

/*
* The call for the program is: 
* ./main filepath samples feature classes
*/
int main(int argc, char *argv[]) {


    srand(time(NULL));
    loadCsv();
    calculateSummaries();

    printSummaries();
   // printf("Split %d rows into train=%d and test=%d rows\n", totalLines, trainingLines, testLines);
   // printf("Accuracy: %f%%\n", getAccuracy());
   // showOff(rand()%testLines);
    return 0;
}