from lib.NaiveBayesClassifier import NaiveBayesClassifier
from lib.FileParser import FileParser

fileParser = FileParser()


fileParser.parseFileDescription("db_tennis.txt")
#fileParser.printDBData()
fileParser.parseCVSPatterns("tennis.data")
#fileParser.printPatterns()

classifier = NaiveBayesClassifier(fileParser)

classifier.train(fileParser.fvector, fileParser.label)
#classifier.printTables()


################## VALIDACION

input_data = ['Sunny', 'Cool', 'High', 'Strong', 'No']
classifier.test(input_data)