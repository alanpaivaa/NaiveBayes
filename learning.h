/**
  ******************************************************************************
  * @file    learning.h
  * @author  Alan Jeferson and Levi Moreira
  * @version V1.0
  * @date    23-August-2016
  * @brief   This file contains all the functions prototypes for the learning
  *          functions used throughout the project.
  *
  ******************************************************************************
  */

#ifndef __LEARNING_H
#define __LEARNING_H
/* Exported functions --------------------------------------------------------*/



float calculateMean(int classNumber, int columnNumber);
float calculateStdev(int classNumber, int columnNumber, float mean);
void calculateSummaries();
float calculateProbability(float x, float mean, float stdev);
float calculateClassProbability(int classNumber, float *inputVector);
int predict(float *inputVector);
float getAccuracy();
float getPrecision(int class);
float getRecall(int class);

#endif /* __UTIL_H */