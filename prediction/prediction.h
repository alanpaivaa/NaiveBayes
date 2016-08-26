/**
 * @file    prediction/prediction.h
 * @author  Alan Jeferson and Levi Moreira
 * @version V1.0
 * @date    23-August-2016
 * @brief   This file contains the prototypes for the
 *          functions contained in prediction/prediction.c.
 * */

#ifndef UNTITLED_PREDICTION_H
#define UNTITLED_PREDICTION_H

float calculateProbability(float x, float mean, float stdev);
float calculateClassProbability(int classNumber, float *inputVector);
int   predict(float *inputVector);
float getAccuracy();
float getPrecision(int class);
float getRecall(int class);
void  calculateMetrics();
void  printMetrics();

#endif //UNTITLED_PREDICTION_H
