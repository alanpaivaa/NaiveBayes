/**
 * @file    training/main.c
 * @author  Alan Jeferson and Levi Moreira
 * @version V1.1.0
 * @date    23-August-2016
 * @brief   This file is the entry point to run the training module. Just run
 *          the main function to get it up and running after setting the proper dataset
 *          in the defines.h file.
 * */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "training.h"
#include "csv.h"


/**
  * @brief Main function.
  *
  * Run it in order to load a full dataset, write a
  * smmaller test dataset and the summaries to other CSV files. Then you can run
  * the prediction module.
  * */
int main(int argc, char *argv[]) {

    srand(time(NULL));

    loadFullDatasetFromCsv(); /* Loading an entire dataset */
    printf("CSV file loaded into training and test sets!\n");

    writeTestsetToCsv(); /* Writing the test set to a csv file */
    printf("Testset written to a CSV file!\n");

    calculateSummaries(); /* Calculating the summaries */
    printf("Summaries calculated!\n");

    writeSummariesToCsv(); /* Writing the summaries to a csv file */
    printf("Summaries written to a CSV file!\n");

    return 0;

}