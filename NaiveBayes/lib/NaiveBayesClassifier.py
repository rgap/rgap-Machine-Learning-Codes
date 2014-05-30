from __future__ import division
import numpy as np

class NaiveBayesClassifier():

    def __init__ (self, fileParser):
        self.prob = []
        self.probtotal = []
        self.prob_class = []
        self.fp = fileParser

    def printTables(self):
        print self.prob
        print "--------------"
        print self.probtotal
        print "--------------"
        print self.prob_class
        print "--------------"


    def train(self, data, label):
        assert(len(data) == len(label))

        for i in range(self.fp.N):
            self.prob.append(np.zeros((len(self.fp.features[i][1]), self.fp.C)))
            self.probtotal.append(np.zeros((len(self.fp.features[i][1]), 1)))            

        # probabilidad de clase
        N_instances = self.fp.ninstances

        for i in range(self.fp.C):
            self.prob_class.append(self.fp.classes_ninstances[i] / N_instances)
        
        # cada tabla

        for i, prob_pos, probtotal_pos in zip(range(self.fp.N),self.prob, self.probtotal):    

            for class_name in self.fp.classes:
                class_value = self.fp.class_value[class_name]
                N_c = self.fp.classes_ninstances[class_value]

                for feature_name in self.fp.features[i][1]:
                    #print class_name + " " + feature_name
                    feature_value = self.fp.feature_value[i][feature_name]

                    N_xc = 0
                    N_xv = 0

                    for fvector, classlabel in zip(data, label):
                        if fvector[i] == feature_value:
                            N_xv += 1                            
                        if classlabel == class_value and fvector[i] == feature_value:
                            N_xc += 1

                    #print (str(N_xc) + ' / ' + str(N_c))

                    prob_pos[feature_value][class_value] =  N_xc / N_c

                    #print ("total = " + str(N_xv) + ' / ' + str(N_instances))
                    probtotal_pos[feature_value][0] =  N_xv / N_instances

                #print "-----------------"

    def test(self, input_data):

        # P(C|X) = P(X|C)*P(C) / P(X)

        P_xc = [1 for i in range(self.fp.C)]
        P_x = 1

        for i in range(self.fp.N):
            P_x *= self.probtotal[i][0]
            for j in range(self.fp.C):
                feature_value = self.fp.feature_value[i][str(input_data[i])]
                P_xc[j] *= self.prob[i][feature_value][j]

        mostProbable = -1
        mostProbable_label = ''
        # predecir resultado
        for i in range(self.fp.C):
            P_cx = P_xc[i]*self.prob_class[i] / P_x

            if P_cx > mostProbable:
                mostProbable = P_cx
                mostProbable_label = self.fp.classes[i]

            print "P(" + self.fp.classes[i] + "|X)" + " = " + str(P_cx)

        print "Clase mas probable = " + mostProbable_label

        return ( 1 if (input_data[-1] == mostProbable_label) else 0)

    def testFile(self, filename):

        sumResult = 0

        with open(filename, 'r') as f:

            ntests = 0
            for line in f.readlines():
                testData = line.replace(" ", "").rstrip().split(',')
                print "TEST "+ str(ntests) + " : " + line.replace("\n", "")
                result = self.test(testData)     
                sumResult += result   
                ntests += 1
                print "------------------------\n"

        print "Exactitud = " + str((sumResult / ntests))
        print "Error = " + str((1 - sumResult / ntests))
