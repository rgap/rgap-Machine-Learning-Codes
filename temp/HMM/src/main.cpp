#include <iostream>
#include <boost/lexical_cast.hpp>
#include "boost/multi_array.hpp"


using namespace std;

#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include <math.h>

#include <list>
#include <map>
#include <cassert>

#include "OpOtras.h"

#include "hmm.h"

int main()
{
	//3 estados, 2 observac
	HMM hmm(3, 2);


	hmm.pi_init(1, 0.33333333);
	hmm.pi_init(2, 0.33333333);
	hmm.pi_init(3, 0.33333333);


	hmm.init(1, 1, 0.33333333);
	hmm.init(1, 2, 0.33333333);
	hmm.init(1, 3, 0.33333333);
	hmm.init(2, 1, 0.33333333);
	hmm.init(2, 2, 0.33333333);
	hmm.init(2, 3, 0.33333333);
	hmm.init(3, 1, 0.33333333);
	hmm.init(3, 2, 0.33333333);
	hmm.init(3, 3, 0.33333333);

	hmm.o_init(1, 'H', 0.5);
	hmm.o_init(2, 'H', 0.75);
	hmm.o_init(3, 'H', 0.25);
	hmm.o_init(1, 'T', 0.5);
	hmm.o_init(2, 'T', 0.25);
	hmm.o_init(3, 'T', 0.75);

	string training;
	string test;

	training = "HHHTTHT";
	test = "HHT";

	cout << "Probability (forward) " << hmm.alpha(training) << endl;

	cout << "Probability (backwards) " << hmm.beta(training) << endl;

	int *best_path = new int[256];
	cout << "Best path : " << hmm.viterbi(training, best_path) << "\n\n";

	hmm.maximize(training, test);

	cout << "Probability Forward: " << endl;
	cout << hmm.alpha(training);
	return 0;
}
