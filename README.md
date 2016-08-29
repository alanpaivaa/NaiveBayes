# NaiveBayes
This is a c implementation of the Machine Learning algorithm called Naive Bayes Gaussian. 
It's been adapted from the python version in: http://machinelearningmastery.com/naive-bayes-classifier-scratch-python/
It will be used in the Embbeded System Module at IFCE to be run in a ARM9 platform.

This algorithm is divided into two steps:
	-Training, where the dataset will be used to generate the summaries (means and standard deviation) intermediate dataset
		This phase happens in a computer 
	-Prediction, where the intermediate dataset + testset will be use to generate the predictions
		The prediction phase is the one that runs in the ARM9 platform

1) Compiling

To get it up and running in a computer, execute the following steps:
1. Select a dataset by commenting/uncommenting the datasets define section at the "defines.h" file;
2. Run the "training/main.c" file to generate the training files;
	This can also be done by running "make -f makefile" inside the training folder
3. Run the "prediction/main.c" file to see the classification report (accuracy, recall, precision etc);
	This can also be done by running "make -f makefile" inside the prediction folder
4. Run your program by typing ./main inside the prediction folder


To compile the code for the ARM9 plataform:
	-Repeat the steps 1 and 2 from a PC
	-Run the command "arm-linux-gcc main.c prediction.c extras.c csv.c -o main -lm" from within the prediction folder in a PC with the ARM compiler
	-In the ARM platform simply run your program by typing ./main from within the prediction folder


2) Project organization
The project was organized based on the STM32F Peripheral Library examples provided by STMicroeletronics followig the guidelines:
	-Each .c file has an .h file with the functions headers
	-The functions were separated according to their purposes
	-The comments can be used to generate automatic documentation


3) Project structure
The project follows the structure:
 .NaiveBayyes - 	root folder
   |-datasets - 	contains all datasets that will be used throughout the execution
   |---full - 		contains the full version of the datasets to be used
   |---summaries	contains the summarised knowledge of the classifier (means and standard deviation for each class and attribute)
   |---test 		contains the test set to be classified 
   |-prediction 	contains the code used to make the predictions (these are the files that execute the algorithm that runs in the ARM platform)
   |-testers		contains the codes for the test code (python with library and original python code)
   |-training 		contains the code used to generate the summaries and test set


