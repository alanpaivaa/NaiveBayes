# Example of Naive Bayes implemented from Scratch in Python
import csv
import random
import math
import numpy

def loadCsv(filename):
	lines = csv.reader(open(filename, "rb"))
	dataset = list(lines)
	for i in range(len(dataset)):
		dataset[i] = [float(x) for x in dataset[i]]
	return dataset

def splitDataset(dataset, splitRatio):
	trainSize = int(len(dataset) * splitRatio) +1
	trainSet = []
	copy = list(dataset)
	index  = 0

	while len(trainSet) < trainSize:
		element = copy.pop(0)
		index = index+1
		trainSet.append(element)

	return [trainSet, copy]

def separateByClass(dataset):
	separated = {}
	for i in range(len(dataset)):
		vector = dataset[i]
		if (vector[-1] not in separated):
			separated[vector[-1]] = []
		separated[vector[-1]].append(vector)
	return separated

def mean(numbers):
	return sum(numbers)/float(len(numbers))

def stdev(numbers):
	avg = mean(numbers)
	variance = sum([pow(x-avg,2) for x in numbers])/float(len(numbers)-1)
	return math.sqrt(variance)

def summarize(dataset):
	summaries = [(mean(attribute), stdev(attribute)) for attribute in zip(*dataset)]
	del summaries[-1]
	return summaries

def summarizeByClass(dataset):
	separated = separateByClass(dataset)
	summaries = {}
	for classValue, instances in separated.iteritems():
		summaries[classValue] = summarize(instances)
	return summaries

def calculateProbability(x, mean, stdev):
	exponent = math.exp(-(math.pow(x-mean,2)/(2*math.pow(stdev,2))))
	res = ((1 / (math.sqrt(2*math.pi) * stdev)) * exponent)

	if(res==0):
		#print res
		return 0
	else:
		#print math.log(res)
		return math.log(res)

def calculateClassProbabilities(summaries, inputVector):
	probabilities = {}
	for classValue, classSummaries in summaries.iteritems():
		probabilities[classValue] = 0
		for i in range(len(classSummaries)):
			mean, stdev = classSummaries[i]
			x = inputVector[i]
			probabilities[classValue] += calculateProbability(x, mean, stdev)
		print probabilities[classValue]
	return probabilities

def predict(summaries, inputVector):
	probabilities = calculateClassProbabilities(summaries, inputVector)
	bestLabel, bestProb = None, -1
	for classValue, probability in probabilities.iteritems():
		if bestLabel is None or probability > bestProb:
			bestProb = probability
			bestLabel = classValue
	return bestLabel

def getPredictions(summaries, testSet):
	predictions = []
	for i in range(len(testSet)):
		result = predict(summaries, testSet[i])
		predictions.append(result)
	return predictions

def getAccuracy(testSet, predictions):
	correct = 0
	for i in range(len(testSet)):
		if testSet[i][-1] == predictions[i]:
			correct += 1
		# print i, predictions[i], testSet[i][-1], testSet[i]
	return (correct/float(len(testSet))) * 100.0

def printSummaries(summaries):
	for a, b in summaries.iteritems():
		print  "Classe %s:" % a
		for s in b:
			print "(%11.6f, %11.6f)" % (s[0], s[1])
		print "\n"

def getConfusionMatriz(testSet,predictions):
	confusionM = numpy.zeros(shape=(10,10))
	for i in range(len(testSet)):
		predicted = int(predictions[i])
		correct = int(testSet[i][-1])
		confusionM[correct, predicted]+=1
	return confusionM


def main():
	filename = 'libras.csv'
	splitRatio = 0.8
	dataset = loadCsv(filename)
	trainingSet, testSet = splitDataset(dataset, splitRatio)
	# for t in trainingSet:
	# 	print  t
	print('Split {0} rows into train={1} and test={2} rows').format(len(dataset), len(trainingSet), len(testSet))
	# prepare model
	summaries = summarizeByClass(trainingSet)

	# test model
	predictions = getPredictions(summaries, testSet)
	accuracy = getAccuracy(testSet, predictions)
	print('Accuracy: {0}%').format(accuracy)

	#printSummaries(summaries)

	#print getConfusionMatriz(testSet,predictions)
	#print summaries[0]

main()