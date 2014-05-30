from lib.NaiveBayesClassifier import NaiveBayesClassifier
from lib.FileParser import FileParser

fileParser = FileParser()


# cvs format
#fileParser.parseDBData("db_car.txt")
#fileParser.printDBData()

# weka format
fileParser.buildFileDescription("car.data", "db_car.txt")
fileParser.parseFileDescription("db_car.txt")
fileParser.parseCVSPatterns("car.data")
#fileParser.printPatterns()

classifier = NaiveBayesClassifier(fileParser)

classifier.train(fileParser.fvector, fileParser.label)
#classifier.printTables()


classifier.testFile("car-prueba.data")


#input_data = ['vhigh', 'vhigh', 2, 2, 'med', 'med', 'unacc']
#classifier.test(input_data)

#input_data = ['low', 'high', 4, 4, 'big', 'med', 'acc']
#classifier.test(input_data)
