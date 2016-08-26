
import numpy as np
import urllib
import sys
import csv
from sklearn.naive_bayes import GaussianNB
from sklearn.metrics import classification_report
from sklearn.metrics import confusion_matrix

file = sys.argv[1]
samples = int(sys.argv[2])
features = int(sys.argv[3])
ratio = 0.8
limit = int(samples*ratio)+1
print samples-limit

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
prediction = clf.predict(testData)
print(score*100)

target_names = ["class 0","class 1","class 2","class 3","class 4","class 5","class 6","class 7","class 8","class 10"]

print(classification_report(testLabel,prediction, target_names=target_names ))

print confusion_matrix(testLabel,prediction)