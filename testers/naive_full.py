
import numpy as np
import urllib
import sys
import csv
from sklearn.naive_bayes import GaussianNB

file = sys.argv[1]
samples = int(sys.argv[2])
features = int(sys.argv[3])
ratio = 0.8
limit = int(samples*ratio)+1
print limit

# url with dataset
#url = "http://archive.ics.uci.edu/ml/machine-learning-databases/pima-indians-diabetes/pima-indians-diabetes.data"
## download the file
#raw_data = urllib.urlopen(url)
# load the CSV file as a numpy matrix
#dataset = np.loadtxt(raw_data, delimiter=",")
#dataset = np.loadtxt(open(file,"rb"),delimiter=",",skiprows=1)
dataset = result=np.array(list(csv.reader(open(file,"rb"),delimiter=','))).astype('float')
# separate the data from the target attributes
trainingData = dataset[0:limit:,0:features]
trainingLabes = dataset[0:limit:,features]


testData = dataset[limit::,0:features]
testLabel = dataset[limit::,features]

clf = GaussianNB()
clf.fit(trainingData,trainingLabes)
score = clf.score(testData,testLabel)
print(score*100)