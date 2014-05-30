class FileParser():

	def __init__(self):
		self.N = 0 # num features
		self.C = 0 # num classes
		self.ninstances = 0

		self.classes = []
		self.features = []
		self.class_value = {}
		self.feature_value = []

		self.classes_ninstances = []

		# patrones
		self.fvector = []
		self.label = []

	def parseFileDescription(self, filename):
	    
	    with open(filename, 'r') as f:
		    self.ninstances = int(f.readline())
		    self.C = int(f.readline())

		    for i in range(self.C):
		    	line = f.readline()
		    	chunks = line.replace(" ", "").rstrip().split(':');
		    	self.classes.append(chunks[0])
		    	self.classes_ninstances.append(int(chunks[1]))

		    	self.class_value[chunks[0]] = i

		    self.N = int(f.readline())

		    for i in range(self.N):
		    	line = f.readline()
		    	
		    	chunks = line.replace(" ", "").rstrip().split(':');
		    	if chunks[-1] == '':
		    		chunks.pop()


		    	self.features.append([])
		    	self.features[i].append(chunks[0])
		    	chunks = chunks[1].replace(" ", "").rstrip().split(',')
		    	if chunks[-1] == '':
		    		chunks.pop()

		    	self.features[i].append([])
		    	self.feature_value.append({})
		    	for j in range(len(chunks)):
		    		self.features[i][1].append(chunks[j])
		    		self.feature_value[i][chunks[j]] = j

	def buildFileDescription(self, filePatterns, fileDescription):
		dbclasses = {}
		dbfeatures = []
		ninstances = 0
		nfeatures = 0
		with open(filePatterns, 'r') as f:
			k = 0
			for line in f.readlines():
				ninstances += 1
				chunks = line.replace(" ", "").rstrip().split(',')
				nfeatures = len(chunks)-1


				for i in range(nfeatures):
					if k == 0: 
						dbfeatures.append({})

					if chunks[i] in dbfeatures[i] and not (dbfeatures[i][chunks[i]] is None):
						dbfeatures[i][chunks[i]] += 1
					else:
						dbfeatures[i][chunks[i]] = 0
				if chunks[-1] in dbclasses and not (dbclasses[chunks[-1]] is None):
					dbclasses[chunks[-1]] += 1
				else:
					dbclasses[chunks[-1]] = 0

				k = 1

		with open(fileDescription, 'w') as f:
			f.write(str(ninstances) + '\n')
			f.write(str(len(dbclasses.keys())) + '\n')
			for key, value in dbclasses.iteritems():
				f.write(str(key) + ' : ' + str(value) + '\n')
			f.write(str(len(dbfeatures)) + '\n')
			
			i = 0
			for featuredict in dbfeatures:
				f.write(chr(ord('A') + i) + ' : ')
				i += 1

				for key, value in featuredict.iteritems():
					f.write(str(key) + ', ')
				f.write('\n')
				

	def parseCVSPatterns(self, filePatterns):

		with open(filePatterns, 'r') as f:

		    for line in f.readlines():

		    	chunks = line.replace(" ", "").rstrip().split(',')
		    	
		    	self.fvector.append([])
		    	for i in range(self.N):
		    		value = self.feature_value[i][chunks[i]]
		    		self.fvector[-1].append(value)

		    	value = self.class_value[chunks[self.N]]
		    	self.label.append(value)

	def printDBData(self):
		print "---------- FILE INFO"
		print "N = " + str(self.N)
		print "C = " + str(self.C)
		print "ninstances = " + str(self.ninstances)
		print self.classes
		print self.features
		print "---------- VALUES"
		print self.feature_value
		print self.class_value

	def printPatterns(self):
		print "---------- FILE INFO"
		print self.fvector
		print self.label
