/**
 * @file    prediction/csv.h
 * @author  Alan Jeferson and Levi Moreira
 * @version V1.1.0
 * @date    25-August-2016
 * @brief   This file contains the prototypes for the
 *          functions contained in prediction/csv.c.
 * */

#ifndef UNTITLED_CSV_H
#define UNTITLED_CSV_H

void loadSummariesFromCsv();
void loadTestsetFromCsv();
void writeMatrixToFile(float *vector, FILE *file, int lines, int columns);

#endif //UNTITLED_CSV_H
