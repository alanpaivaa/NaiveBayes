/**
 * @file    training/training.h
 * @author  Alan Jeferson and Levi Moreira
 * @version V1.1.0
 * @date    25-August-2016
 * @brief   This file contains the headers for the implementations in
 *          training/training.c.
 * */

#ifndef UNTITLED_TRAINING_H
#define UNTITLED_TRAINING_H

void  calculateSummaries();
float calculateStdev(int classNumber, int columnNumber, float mean);
float calculateMean(int classNumber, int columnNumber);
#endif //UNTITLED_TRAINING_H