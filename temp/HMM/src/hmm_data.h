#ifndef HMM_DATA_H
#define HMM_DATA_H


#include <iostream>
#include <string>
#include <math.h>

using namespace std;

class Data {

	private:

		double **transitions;
		double **emissions;
		double *pi_transitions;

	public:
		Data(int n=0, int m=0)
		{
			transitions = new double* [n+1];
			for(int i=0; (i <= n+1); i++)
			{
				transitions[i] = new double[n+1];
			}
			emissions = new double*[n+1];

			for(int i=0; (i <= n+1); i++)
			{
				emissions[i] = new double[m+1];
			}

			pi_transitions = new double[n+1];
		}

		double get_transitions(int i, int j)
		{
			return transitions[i][j];
		}

		double get_emission(int i, int j)
		{
			return emissions[i][j];
		}

		double get_pi_transitions(int i)
		{
			return pi_transitions[i];
		}

		void set_transition(int i, int j, double v)
		{
			transitions[i][j] = v;
		}

		void set_emission(int i, int j, double v)
		{
			this->emissions[i][j] = v;
		}

		void set_pi_transition(int i, double v)
		{
			pi_transitions[i] = v;
		}
};

#endif /* HMM_DATA_H */
