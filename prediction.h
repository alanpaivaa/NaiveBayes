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

#ifndef UNTITLED_PREDICTION_H
#define UNTITLED_PREDICTION_H

float calculateProbability(float x, float mean, float stdev);
float calculateClassProbability(int classNumber, float *inputVector);
int   predict(float *inputVector);
float getAccuracy();
float getPrecision(int class);
float getRecall(int class);
void  calculateMetrics();

#endif //UNTITLED_PREDICTION_H
